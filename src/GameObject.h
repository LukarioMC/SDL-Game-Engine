#pragma once

#include "Game.h"

class GameObject
{
public:
    GameObject(const char *path, float x, float y, float velocity);
    ~GameObject();

    void update(float deltaTime);
    void draw();

    float xVel{}, yVel{};

private:
    float xPos{}, yPos{};

    SDL_Texture *texture = nullptr;
    SDL_FRect srcRect{}, dstRect{};
};