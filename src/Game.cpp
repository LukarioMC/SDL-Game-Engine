#include <iostream>
#include <ostream>

#include "Game.h"
#include "Map.h"
#include "TextureManager.h"

Map *map = nullptr;

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
    // Add entities
    auto &player(world.createEntity());
    auto &playerTransform = player.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);
    auto &playerVelocity = player.addComponent<Velocity>(Vector2D(10, 0), 60.0f);

    SDL_Texture *tex = TextureManager::load("../asset/mario.png");
    SDL_FRect playerSrc{0, 0, 32, 44};
    SDL_FRect playerDst{playerTransform.position.x, playerTransform.position.y, 64, 88};
    player.addComponent<Sprite>(tex, playerSrc, playerDst);
}

void Game::handleEvents()
{
    // ? Why handle only one event per frame??
    // Check for next event, if there is one, remove it from the queue and store it in our event variable
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

void Game::update(float dt)
{
    world.update(dt, event);
}

void Game::render()
{
    // Sets the default colour to draw with
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // Clear the renderer with the draw colour
    SDL_RenderClear(renderer);

    // Subsystems/other drawing goes below.
    map->draw();
    world.render();

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