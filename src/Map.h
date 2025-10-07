#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include <Component.h>

class Map
{
public:
    Map() = default;
    ~Map() = default;

    void load(const char *path, SDL_Texture *tex);
    void draw();

    SDL_Texture *tileset = nullptr;
    int width{}, height{}, tileWidth{}, tileHeight{};
    std::vector<std::vector<int>> tileData;
    std::vector<Collider> colliders;
};