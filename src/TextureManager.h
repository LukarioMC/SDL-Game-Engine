#pragma once
#include "Game.h"
#include <SDL3_image/SDL_image.h>

class TextureManager
{
public:
    static SDL_Texture *load(const char *path);

    static void draw(SDL_Texture *texture, SDL_FRect src, SDL_FRect dst);
};