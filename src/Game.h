#pragma once

#include <SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>

#include <memory>
#include <vector>
#include "Enemy.h"

class Renderer;
class Input;
class Player;
class BackgroundImage;
class TileMap;

class Panel;
class Button;
class GuiRenderer;

struct GameState
{
	std::vector<float> lanePositionsX;
};

typedef std::vector<std::unique_ptr<Enemy>> tEnemiesVec;

class Game
{
public:
	Game() {}
	bool Init(int width, int height, bool fullscreen, const char* title);
	void Run();

	const GameState& GetGameState() const { return gameState; }
private:
	void SetupGL();
	void Cleanup();

	SDL_Window* m_window;
	SDL_GLContext m_context;
	int m_windowWidth;
	int m_windowHeight;
	int m_viewportWidth;
	int m_viewportHeight;
	Renderer* m_renderer;
	Input* m_input;
	GuiRenderer* m_guiRenderer;

private:
	void HandleInput();
	void Update(float dt);
	void Create(); // scene related
	void Render(); // scene related
	void Destroy(); // scene related

	Player* m_player;
	tEnemiesVec m_enemies;

	Texture* m_wizardTexture;
	Texture* m_blackMageTexture;
	Texture* m_backgroundTexture;
	Texture* m_tileMapTexture;
	
	BackgroundImage* m_backgroundImage;
	
	GameState gameState;

	TileMap* m_tileMap;

	Panel* m_viewpointPanel;
	Panel* m_testPanel;
	Button* m_button;

};
