#pragma once

#include <SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>

#include <memory>
#include <vector>
#include "SpriteEntity.h"

class Renderer;
class Input;
class Player;

class Game
{
public:
    Game() {}
    bool Init(int width, int height, bool fullscreen, const char* title);
    void Run();

private:
    void SetupGL();
    void Create(); // scene related
    void HandleInput();
    void Update(float dt);
    void Render(); // scene related
    void Destroy(); // scene related
    void Cleanup();

    SDL_Window* m_window;
    SDL_GLContext m_context;
    int m_windowWidth;
    int m_windowHeight;
    int m_viewportWidth;
    int m_viewportHeight;
    Renderer* m_renderer;
    Input* m_input;

private:
    Player* m_player;
    std::vector<std::unique_ptr<SpriteEntity>> m_spriteEntities;

};
