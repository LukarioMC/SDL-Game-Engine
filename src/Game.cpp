#include <iostream>
#include <ostream>

#include "Game.h"
#include "GameObject.h"
#include "Map.h"

Map *map = nullptr;
GameObject *player = nullptr;

Game::Game()
{
}

Game::~Game()
{
    destroy();
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Initialize the SDL library and show a window
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 1)
    {
        std::cout << "SDL Subsystem Initialized..." << std::endl;
        window = SDL_CreateWindow(title, width, height, flags);

        if (window)
        {
            std::cout << "Windows created..." << std::endl;
        }

        // Create the renderer, passing `nullptr` will use the OS default (Win = Direct3D, Mac = Metal, OpenGL)
        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer)
        {
            std::cout << "Renderer created..." << std::endl;
        }
        else
        {
            std::cout << "Renderer could not be created!" << std::endl;
            return;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    // Load map data
    map = new Map();
    player = new GameObject("../asset/ball.png", 0, 0, 60.0f);
}

void Game::handleEvents()
{
    // SDL listens to the OS for input events and adds them into a queue
    SDL_Event event;
    // Check foro next event, if there is one, remove it from the queue and store it in our event variable
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_EVENT_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update(Uint64 elapsedMs)
{
    frameCount++;
    // std::cout << frameCount << std::endl;
    deltaTime = (elapsedMs - lastFrameTimestamp) / 1000.0f;
    lastFrameTimestamp = elapsedMs;

    player->update(deltaTime);
}

void Game::render()
{
    // Sets the default colour to draw with
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // Clear the renderer with the draw colour
    SDL_RenderClear(renderer);

    // Subsystems/other drawing goes below.
    map->draw();
    player->draw();

    // Display everything that was drawn to the screen.
    // First draws it to a back buffer and swaps the buffer to the screen.
    SDL_RenderPresent(renderer);
}

void Game::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game was destroyed, used memory should be clear." << std::endl;
}

void Game::randomizeRendererColor()
{
    r = std::rand() % 256;
    g = std::rand() % 256;
    b = std::rand() % 256;
    a = 255;
}