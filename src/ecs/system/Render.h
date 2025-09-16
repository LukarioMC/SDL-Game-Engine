#pragma once
#include <vector>
#include <memory>

#include <Entity.h>
#include <Component.h>
#include <TextureManager.h>

class RenderSystem
{
public:
    void render(const std::vector<std::unique_ptr<Entity>> &entities)
    {
        for (auto &entity : entities)
        {
            if (entity->hasComponent<Position>() && entity->hasComponent<Sprite>())
            {
                auto &position = entity->getComponent<Position>();
                auto &sprite = entity->getComponent<Sprite>();
                sprite.dst.x = position.x;
                sprite.dst.y = position.y;
                TextureManager::draw(sprite.texture, sprite.src, sprite.dst);
            }
        }
    }
};