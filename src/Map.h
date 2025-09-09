#pragma once

#include "Game.h"

class Map
{
public:
    Map();
    ~Map();

    void load(int data[10][15]);
    void draw();

private:
    // Brace initialization to make the struct values within all zereo'd
    SDL_FRect src{}, dest{};
    SDL_Texture *water = nullptr;
    SDL_Texture *dirt = nullptr;
    SDL_Texture *grass = nullptr;

    int map[10][15]{};
};