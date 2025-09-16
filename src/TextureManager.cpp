#include <iostream>
#include <ostream>

#include "TextureManager.h"
#include "Game.h"

// Just grab the game object reference
extern Game *game;

// Load texture with path
SDL_Texture *TextureManager::load(const char *path)
{
    // A surface represents an image loaded in CPU RAM
    SDL_Surface *tempSurface = IMG_Load(path);
    if (!tempSurface)
    {
        std::cout << "Failed to load image: " << path << std::endl;
    }
    // A *texture* represents an image loaded in VRAM
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->getRenderer(), tempSurface);

    // Cleanup
    SDL_DestroySurface(tempSurface);

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_FRect src, SDL_FRect dst)
{
    // Draw to the screen
    SDL_RenderTexture(game->getRenderer(), texture, &src, &dst);
}