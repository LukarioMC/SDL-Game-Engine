#pragma once

#include "Game.h"

class GameObject
{
public:
    GameObject(const char *path, int x, int y);
    ~GameObject();

    void update();
    void draw();

private:
    int xPos{}, yPos{};

    SDL_Texture *texture = nullptr;
    SDL_FRect srcRect{}, dstRect{};
};