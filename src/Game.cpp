#include <iostream>
#include <ostream>

#include "Game.h"
#include "TextureManager.h"
#include "AssetManager.h"

std::function<void(std::string)> Game::onSceneChangeRequest;

Game::Game()
{
}

Game::~Game()
{
    destroy();
}

void Game::init(const char *title, int windowWidth, int windowHeight, bool fullscreen)
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
        window = SDL_CreateWindow(title, windowWidth, windowHeight, flags);

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

    // Load assets
    AssetManager::loadAnimation("player", "../asset/animations/chick_animations.xml");
    AssetManager::loadAnimation("enemy", "../asset/animations/bird_animations.xml");

    // Load scenes
    sceneManager.loadScene("level1", "../asset/map.tmx", windowWidth, windowHeight);
    sceneManager.loadScene("level2", "../asset/map2.tmx", windowWidth, windowHeight);

    // Start the first scene
    sceneManager.changeSceneDeferred("level1");

    // Scene callback
    onSceneChangeRequest = [this](std::string sceneName)
    {
        // ======== Some game state logic ========
        if (sceneManager.currentScene->getName() == "level2" && sceneName == "level2")
        {
            std::cout << "You won!" << std::endl;
            isRunning = false;
            return;
        }

        if (sceneName == "gameover")
        {
            std::cout << "Game over!" << std::endl;
            isRunning = false;
            return;
        }
        // ======== end game state logic ========

        sceneManager.changeSceneDeferred(sceneName);
    };
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
    sceneManager.update(dt, event);
}

void Game::render()
{
    // Sets the default colour to draw with
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // Clear the renderer with the draw colour
    SDL_RenderClear(renderer);

    sceneManager.render();

    // Display everything that was drawn to the screen.
    // First draws it to a back buffer and swaps the buffer to the screen.
    SDL_RenderPresent(renderer);
}

void Game::destroy()
{
    TextureManager::clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game was destroyed, used memory should be clear." << std::endl;
}
