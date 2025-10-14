#include <iostream>
#include <ostream>

#include "Game.h"
#include "TextureManager.h"
#include "AssetManager.h"

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

    AssetManager::loadAnimation("player", "../asset/animations/bull_animations.xml");

    world.getMap().load("../asset/map.tmx", TextureManager::load("../asset/spritesheet_terrain.png"));
    // Add entities
    for (auto &collider : world.getMap().colliders)
    {
        auto &e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto &c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        SDL_Texture *tex = TextureManager::load("../asset/spritesheet_terrain.png");
        SDL_FRect colSrc{0, 32, 32, 32};
        SDL_FRect colDst{c.rect.x, c.rect.y, c.rect.w, c.rect.h};
        e.addComponent<Sprite>(tex, colSrc, colDst);
    }
    // Player
    auto &player(world.createEntity());
    auto &playerTransform = player.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);
    auto &playerVelocity = player.addComponent<Velocity>(Vector2D(0, 0), 120.0f);

    Animation animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture *playerTex = TextureManager::load("../asset/animations/bull_anim.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0];
    SDL_FRect playerDst{playerTransform.position.x, playerTransform.position.y, 64, 64};

    // SDL_Texture *playerTex = TextureManager::load("../asset/mario.png");
    // SDL_FRect playerSrc{0, 0, 32, 44};
    // SDL_FRect playerDst{playerTransform.position.x, playerTransform.position.y, 64, 88};

    player.addComponent<Sprite>(playerTex, playerSrc, playerDst);

    auto &playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    // Coin Items
    for (auto point : world.getMap().itemSpawns)
    {
        auto &item(world.createEntity());
        auto &itemTransform = item.addComponent<Transform>(Vector2D(point.x - 16, point.y - 16), 0.0f, 1.0f);

        SDL_Texture *itemTex = TextureManager::load("../asset/coin.png");
        SDL_FRect itemSrc{0, 0, 32, 32};
        SDL_FRect itemDst{itemTransform.position.x, itemTransform.position.y, 32, 32};
        item.addComponent<Sprite>(itemTex, itemSrc, itemDst);

        auto &itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDst.w;
        itemCollider.rect.h = itemDst.h;
    }
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
    world.render();

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

void Game::randomizeRendererColor()
{
    r = std::rand() % 256;
    g = std::rand() % 256;
    b = std::rand() % 256;
    a = 255;
}