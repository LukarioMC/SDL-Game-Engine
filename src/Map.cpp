#include "Map.h"
#include "TextureManager.h"

int mapData[10][15] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 0},
    {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0},
    {0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0},
    {0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 2, 2, 1, 2, 2, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
};

Map::Map() : water(TextureManager::load("../asset/water.png")),
             dirt(TextureManager::load("../asset/dirt.png")),
             grass(TextureManager::load("../asset/grass.png"))
{
    load(mapData);

    // What part of the images do we want?
    src.x = src.y = 0;
    src.w = src.h = 32;

    // Where should they be displayed?
    dest.x = dest.y = 0;
    dest.w = dest.h = 64;
}

Map::~Map()
{
    if (water)
        SDL_DestroyTexture(water);
    if (dirt)
        SDL_DestroyTexture(dirt);
    if (grass)
        SDL_DestroyTexture(grass);
}

void Map::load(int data[10][15])
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 15; col++)
        {
            map[row][col] = data[row][col];
        }
    }
}

void Map::draw()
{
    int type = 0;

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 15; col++)
        {
            type = map[row][col];

            dest.y = static_cast<float>(row) * 64;
            dest.x = static_cast<float>(col) * 64;

            switch (type)
            {
            case 0:
                TextureManager::draw(water, src, dest);
                break;
            case 1:
                TextureManager::draw(dirt, src, dest);
                break;
            case 2:
                TextureManager::draw(grass, src, dest);
                break;

            default:
                break;
            }
        }
    }
}