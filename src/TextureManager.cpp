#include <iostream>
#include <ostream>

#include "TextureManager.h"
#include "Game.h"

// Just grab the game object reference
extern Game *game;
std::unordered_map<std::string, SDL_Texture *> TextureManager::textures;

// Load texture with path
SDL_Texture *TextureManager::load(const char *path)
{
    // Use a cache textures for faster loading.
    auto it = textures.find(path);
    if (it != textures.end())
    {
        return it->second;
    }

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

    // Check if successfully created a texture
    if (!texture)
    {
        std::cout << "Failed to create texture: " << path << std::endl;
        return nullptr;
    }
    // Store in cache
    textures[path] = texture;

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_FRect src, SDL_FRect dst)
{
    // Draw to the screen
    SDL_RenderTexture(game->getRenderer(), texture, &src, &dst);
}

void TextureManager::clean()
{
    for (auto &pair : textures)
    {
        SDL_DestroyTexture(pair.second);
        pair.second = nullptr;
    }
    textures.clear();
}