#include <iostream>

#include "Game.h"

// Global Vars
Game *game = nullptr;

int main()
{
    const int FPS = 144;                     // Target FPS
    const int desiredFrameTime = 1000 / FPS; // Target ms per frame

    // Stores the milliseconds the program has been running for (in total)
    Uint64 ticks = SDL_GetTicks();
    // Stores the milliseconds (as of the beginning of the last frame)
    Uint64 lastFrameTicks = ticks;
    // Stores the milliseconds per each frame (events + update + render)
    int actualFrameTime = 0;
    // The time warp/scaling factor used in simulating game objects (ticks - lastFrameTicks) / 1000
    float dt = 0.0f;

    game = new Game(); // Will need to manually clean this up later
    game->init("8552 Tutorial Engine", 800, 600, false);

    while (game->running())
    {
        lastFrameTicks = ticks;
        ticks = SDL_GetTicks();
        dt = (ticks - lastFrameTicks) / 1000.0f;

        // Handle game logic and rendering
        game->handleEvents();
        game->update(dt);
        game->render();

        // Get elapsed time in ms of the last frame
        actualFrameTime = SDL_GetTicks() - ticks;

        // Frame limiter, keep the game running at desired frame rate.
        // If the actual frame time took less time than our desired frame time, delay by their difference
        if (desiredFrameTime > actualFrameTime)
        {
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }
    }

    // Cleanup game
    delete game;

    return 0;
}