#include <iostream>

#include "Game.h"

// Global Vars
Game *game = nullptr;

int main()
{
    const int FPS = 144;                     // Target FPS
    const int desiredFrameTime = 1000 / FPS; // Target time per frame

    Uint64 ticks;
    int actualFrameTime;

    game = new Game(); // Will need to manually clean this up later
    game->init("8552 Tutorial Engine", 800, 600, false);

    while (game->running())
    {
        ticks = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        actualFrameTime = SDL_GetTicks() - ticks; // Elapsed time in ms of the last frame

        // Frame limiter, keep the game running at desired frame rate.
        // If the actual frame time took less time than our desired frame time, delay by their difference
        if (desiredFrameTime > actualFrameTime)
        {
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }

        if (actualFrameTime > desiredFrameTime)
        {
            std::cout << "Frame took longer than expected! Actual frame ms: " << actualFrameTime << std::endl;
        }
    }

    // Cleanup game
    delete game;

    return 0;
}