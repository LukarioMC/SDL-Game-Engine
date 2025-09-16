#pragma once
#include <SDL3/SDL.h>
#include "World.h"

class Game
{
public:
    Game();
    ~Game();

    // These types are required as SDL uses these
    void init(const char *title, int width, int height, bool fullscreen);

    // Game Loop functions
    void handleEvents();   // Checks input + system events
    void update(float dt); // Handles game logic and state
    void render();         // Draws current game state to the screen

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

    World world;

    void randomizeRendererColor();

private:
    bool isRunning = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // SDL uses  unsigned 8-bit colour channels (0-255)
    Uint8 r, g, b, a;
};