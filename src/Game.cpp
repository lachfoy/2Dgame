#include "Game.h"

#include "Renderer.h"
#include "DebugRenderer.h"
#include "Input.h"
#include <iostream>
#include "Player.h"
#include "Turret.h"
#include "Texture.h"
#include "TileMap.h"
#include "Panel.h"
#include "Button.h"
#include "GuiRenderer.h"

void RenderChildren(Panel* panel)
{
	if (panel)
	{
		//printf("Rendering %s...\n", panel->GetName());
		
		panel->Render();
		panel->DebugRenderBounds();

		for (Panel* child : panel->GetChildren())
		{
			RenderChildren(child);
		}
	}
}

bool PropogateInput(Panel* panel, Input* input)
{
	bool inputHandled = false;

	if (panel)
	{
		if (panel->HandleInput(input))
		{
			inputHandled = true;
		}

		for (Panel* child : panel->GetChildren())
		{
			if (PropogateInput(child, input))
			{
				inputHandled = true;
				break;
			}
		}
	}

	return inputHandled;
}

bool Game::Init(int width, int height, bool fullscreen, const char* title)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_viewportWidth = m_windowWidth / 2; // for now
	m_viewportHeight = m_windowHeight / 2; // for now

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "An error occurred while initializing SDL2:" << SDL_GetError() << ".\n";
		return false;
	}

	Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if (fullscreen)
	{
		//windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		SDL_DisplayMode displayMode;
		SDL_GetDesktopDisplayMode(0, &displayMode); // can return int error
		m_windowWidth = displayMode.w;
		m_windowHeight = displayMode.h;

		//m_viewportWidth = m_windowWidth;
		//m_viewportHeight = m_windowHeight;

		windowFlags |= SDL_WINDOW_BORDERLESS;
	}

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, windowFlags);
	if (!m_window)
	{
		std::cerr << "An error occurred while creating an SDL2 window:" << SDL_GetError() << ".\n";
		SDL_Quit();
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		printf("GL Context could not be created: %s\n", SDL_GetError());
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("GLAD could not be loaded\n");
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	SetupGL();

	// Init systems
	m_renderer = new Renderer();
	m_renderer->Init();
	m_renderer->SetProjection(m_viewportWidth, m_viewportHeight);

	m_debugRenderer = new DebugRenderer();
	m_debugRenderer->Init();
	m_debugRenderer->SetProjection(m_viewportWidth, m_viewportHeight);

	m_guiRenderer = new GuiRenderer();
	m_guiRenderer->Init();
	m_guiRenderer->SetProjection(m_viewportWidth, m_viewportHeight);

	m_input = new Input();

	return true;
}

void Game::Run()
{
	Create();

	Uint32 last_time = 0;

	int fps = 0;
	int fps_count = 0;
	float fps_interval = 0.0f;

	// main loop
	bool running = true;
	while (running)
	{
		running = m_input->HandleEvents();
		HandleInput();
		m_input->Update();

		// calculate delta time
		Uint32 current_time = SDL_GetTicks();
		float dt = (current_time - last_time) / 1000.0f;
		last_time = current_time;

		// calculate fps
		fps_count++;
		fps_interval += dt;
		if (fps_interval > 1.0f)
		{
			fps = fps_count;
			fps_count = 0;
			fps_interval = 0.0f;
		}

		// update
		Update(dt);
		m_debugRenderer->Update(dt);

		// render
		//glClear(GL_COLOR_BUFFER_BIT);
		Render();
		m_renderer->RenderObjects();
		m_debugRenderer->Render();
		m_guiRenderer->RenderQuads();
		//m_guiRenderer->Render();

		// swap buffers
		SDL_GL_SwapWindow(m_window);
	}

	Destroy();
	Cleanup();
}

void Game::SetupGL()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, m_windowWidth, m_windowHeight);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::Create()
{
	m_playerTexture = new Texture("data/images/guy.png");
	m_turretTexture = new Texture("data/images/turret.png");
	m_enemyTexture = new Texture("data/images/droid.png");
	m_tileMapTexture = new Texture("data/images/tile.png");

	m_player = new Player(m_renderer, m_debugRenderer, m_playerTexture);

	m_player->SetPosition(glm::vec2(rand() % m_viewportWidth, rand() % m_viewportHeight));

	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy(m_renderer, m_debugRenderer, m_enemyTexture, m_player);
		enemy->SetPosition(glm::vec2(rand() % m_viewportWidth, rand() % m_viewportHeight));
		m_enemies.push_back(std::unique_ptr<Enemy>(enemy));
	}

	m_turret = new Turret(m_renderer, m_debugRenderer, m_turretTexture, &m_enemies);
	m_turret->SetPosition(glm::vec2(200, 150));

	m_tileMap = new TileMap(m_renderer, m_tileMapTexture);
	m_tileMap->CreateDebugMap();
	m_tileMap->BuildTileMesh();

	// GUI test stuff
	m_rootPanel = new Panel("Root", m_guiRenderer, glm::vec2(0, 0), glm::vec2(m_viewportWidth, m_viewportHeight));

	m_testPanel = new Panel("Panel", m_guiRenderer, glm::vec2(0, 0), glm::vec2(150, 170));
	m_rootPanel->AddChild(m_testPanel);
	m_testPanel->SetColor(glm::vec4(0.4, 0.4, 0.4, 1));
	m_testPanel->CenterX();
	m_testPanel->CenterY();

	m_button1 = new Button("Button1", m_guiRenderer);
	m_testPanel->AddChild(m_button1);
	m_button1->SetPosition(glm::vec2(25, 20));
	m_button1->SetSize(glm::vec2(100, 30));
	m_button1->AddCallback([]()
		{
			printf("Button1 callback!\n");
		});


	m_button2 = new Button("Button2", m_guiRenderer);
	m_testPanel->AddChild(m_button2);
	m_button2->SetPosition(glm::vec2(25, 70));
	m_button2->SetSize(glm::vec2(100, 30));
	m_button2->AddCallback([]()
		{
			printf("Button2 callback!\n");
		});


	m_button3 = new Button("Button3", m_guiRenderer);
	m_testPanel->AddChild(m_button3);
	m_button3->SetPosition(glm::vec2(25, 120));
	m_button3->SetSize(glm::vec2(100, 30));
	m_button3->SetEnabled(false);
}

void Game::HandleInput()
{
	m_player->HandleInput(m_input);

	PropogateInput(m_rootPanel, m_input);
}

void Game::Update(float dt)
{
	m_player->Update(dt);

	m_turret->Update(dt);

	for (const auto& enemy : m_enemies)
	{
		enemy->Update(dt);
	}

	for (const auto& enemy : m_enemies)
	{
		if (Collision(*m_player, *enemy))
		{
			std::cout << "Collided\n";
		}
	}
}

void Game::Render()
{
	m_tileMap->Render();

	for (const auto& enemy : m_enemies)
	{
		enemy->Render();
	}

	m_player->Render();

	m_turret->Render();

	//RenderChildren(m_rootPanel);
}

void Game::Destroy()
{
	delete m_playerTexture;
	delete m_turretTexture;
	delete m_enemyTexture;

	delete m_tileMapTexture;

	m_tileMap->Destroy();
	delete m_tileMap;

	delete m_player;
	m_player = nullptr;

	delete m_turret;
	m_turret = nullptr;
}

void Game::Cleanup()
{
	m_renderer->Dispose();
	delete m_renderer;
	m_renderer = nullptr;

	m_debugRenderer->Dispose();
	delete m_debugRenderer;
	m_debugRenderer = nullptr;

	m_guiRenderer->Dispose();
	delete m_guiRenderer;
	
	delete m_input;
	m_input = nullptr;

	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}
