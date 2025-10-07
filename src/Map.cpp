#include "Map.h"
#include "TextureManager.h"
#include <sstream>
#include <tinyxml2.h>

void Map::load(const char *path, SDL_Texture *tex)
{
    tileset = tex;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    // Get width and height of the map
    auto *mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");
    tileWidth = mapNode->IntAttribute("tilewidth");
    tileHeight = mapNode->IntAttribute("tileheight");
    // Parse terrain data
    auto *layer = mapNode->FirstChildElement("layer");
    auto *data = layer->FirstChildElement("data");
    std::string csv = data->GetText();
    std::stringstream ss(csv);
    tileData = std::vector(height, std::vector<int>(width));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::string val;
            if (!std::getline(ss, val, ','))
                break;
            tileData[i][j] = std::stoi(val); // String to int conversion
        }
    }
    // Parse collider data
    auto *objectGroup = layer->NextSiblingElement("objectgroup");
    for (auto *obj = objectGroup->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object"))
    {
        Collider c;
        c.rect.x = obj->FloatAttribute("x");
        c.rect.y = obj->FloatAttribute("y");
        c.rect.w = obj->FloatAttribute("width");
        c.rect.h = obj->FloatAttribute("height");
        colliders.push_back(c);
    }
    // Parse item spawn data
    // !Make sure the order is correct?
    auto *itemSpawnGroup = objectGroup->NextSiblingElement("objectgroup");
    for (auto *obj = itemSpawnGroup->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object"))
    {
        float x = obj->FloatAttribute("x");
        float y = obj->FloatAttribute("y");
        itemSpawns.push_back(Vector2D(x, y));
    }
}

void Map::draw()
{
    SDL_FRect src{}, dest{};

    dest.w = tileWidth;
    dest.h = tileHeight;

    int type = 0;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            type = tileData[row][col];

            dest.y = static_cast<float>(row) * dest.w;
            dest.x = static_cast<float>(col) * dest.h;

            switch (type)
            {
            case 1:
                // Dirt
                src.x = 0;
                src.y = 0;
                break;
            case 2:
                // Grass
                src.x = tileWidth * 1;
                src.y = 0;
                break;
            case 4:
                // Water
                src.x = tileWidth * 1;
                src.y = tileHeight * 1;
                break;

            default:
                break;
            }
            src.w = tileWidth;
            src.h = tileHeight;

            TextureManager::draw(tileset, src, dest);
        }
    }
}