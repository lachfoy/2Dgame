#include "Game.h"

#include "Renderer.h"
#include "Input.h"
#include <iostream>
#include "Player.h"

bool Game::Init(int width, int height, bool fullscreen, const char* title)
{
    m_windowWidth = width;
    m_windowHeight = height;
    m_viewportWidth = width; // for now
    m_viewportHeight = height; // for now

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "An error occurred while initializing SDL2:" << SDL_GetError() << ".\n";
        return false;
    }

    Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if (fullscreen)
        windowFlags |= SDL_WINDOW_FULLSCREEN;

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

        // render
        Render();
        m_renderer->Render();

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Game::Create()
{
    m_player = new Player(m_renderer);
    m_player->SetWorldPosition(glm::vec3(300.0f, 300.0f, 0.0f));
    // Create some sprites
    //for (int i = 0; i < 1000; i++) {
    //    SpriteEntity* spriteEntity = new SpriteEntity(m_renderer);
    //    spriteEntity->SetWorldPosition(glm::vec3(rand() % m_viewportWidth, rand() % m_viewportHeight, 0.0f));
    //    m_spriteEntities.push_back(std::unique_ptr<SpriteEntity>(spriteEntity));
    //}
}

void Game::HandleInput()
{
    m_player->HandleInput(m_input);
}

void Game::Update(float dt)
{
    m_player->Update(dt);
}

void Game::Render()
{
    m_player->Render();

    //glBindTexture(GL_TEXTURE_2D, textureID);
    //for (const auto& spriteEntity : m_spriteEntities) spriteEntity->Render();
}

void Game::Destroy()
{
    delete m_player;
    m_player = nullptr;

}

void Game::Cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
    
    delete m_input;
    m_input = nullptr;

    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);

    SDL_Quit();
}
