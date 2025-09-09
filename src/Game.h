#pragma once
#include <SDL3/SDL.h>

class Game
{
public:
    Game();
    ~Game();

    // These types are required as SDL uses these
    void init(const char *title, int width, int height, bool fullscreen);

    // Game Loop functions
    void handleEvents();           // Checks input + system events
    void update(Uint64 elapsedMs); // Handles game logic and state
    void render();                 // Draws current game state to the screen

    // Used to free resources
    void destroy();

    bool running()
    {
        return isRunning;
    }

    SDL_Renderer *getRenderer()
    {
        return renderer;
    }

    void randomizeRendererColor();

private:
    int frameCount = 0;
    bool isRunning = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // SDL uses  unsigned 8-bit colour channels (0-255)
    Uint8 r, g, b, a;

    Uint64 lastFrameTimestamp = 0;
    float deltaTime = 0.0f;
};