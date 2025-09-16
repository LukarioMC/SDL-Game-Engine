#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

struct Position
{
    float x = 0.0f;
    float y = 0.0f;
};

struct Sprite
{
    SDL_Texture *texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
};