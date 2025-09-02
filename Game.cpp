#include "Game.h"

#include <iostream>
#include <ostream>

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

void Game::update()
{
    frameCount++;
    std::cout << frameCount << std::endl;
}

void Game::render()
{
    r = 100;
    g = 255;
    b = 50;
    a = 255;

    // Sets the default colour to draw with
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // Clear the renderer with the draw colour
    SDL_RenderClear(renderer);

    // TODO: Drawing goes here

    // Display everything that was drawn to the screen.
    // First draws it to a back buffer and swaps the buffer to the screen.
    SDL_RenderPresent(renderer);
}

void Game::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game was destroyed/memory should be cleaned" << std::endl;
}