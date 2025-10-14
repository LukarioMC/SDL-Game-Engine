#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <Vector2D.h>
#include <unordered_map>
#include <string>

#include "AnimationClip.h"

struct Transform
{
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};
};

struct Velocity
{
    Vector2D direction{};
    float speed{};
};

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

struct Collider
{
    std::string tag;
    SDL_FRect rect{};
};

struct Animation
{
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip;
    float time{};       // Accumulated over current frame
    int currentFrame{}; // Current frame index
    float speed = 0.1f; // Time per frame
};

struct Camera
{
    SDL_FRect view;
    float worldWidth;
    float worldHeight;
};

struct PlayerTag
{
};