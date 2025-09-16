#include <iostream>

#include "Game.h"

// Global Vars
Game *game = nullptr;

int main()
{
    const int FPS = 144;                     // Target FPS
    const int desiredFrameTime = 1000 / FPS; // Target ms per frame

    Uint64 ticks;        // Stores the total MILLISECONDS the program has been running for
    int actualFrameTime; // Stores the MILLISECONDS for each frame
    float dt = 1.0f;

    game = new Game(); // Will need to manually clean this up later
    game->init("8552 Tutorial Engine", 800, 600, false);

    while (game->running())
    {
        ticks = SDL_GetTicks();

        // Handle game logic and rendering
        game->handleEvents();
        game->update(dt);
        game->render();

        // Get elapsed time in ms of the last frame
        actualFrameTime = SDL_GetTicks() - ticks;
        dt = actualFrameTime / 1000.0f;

        // Frame limiter, keep the game running at desired frame rate.
        // If the actual frame time took less time than our desired frame time, delay by their difference
        if (desiredFrameTime > actualFrameTime)
        {
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }

        // Logs when a frame takes longer than expected
        // if (actualFrameTime > desiredFrameTime)
        // {
        //     std::cout << "Frame took longer than expected! Actual frame ms: " << actualFrameTime << std::endl;
        // }
    }

    // Cleanup game
    delete game;

    return 0;
}