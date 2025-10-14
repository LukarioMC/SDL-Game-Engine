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
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>())
            {
                auto &t = entity->getComponent<Transform>();
                auto &sprite = entity->getComponent<Sprite>();
                sprite.dst.x = t.position.x;
                sprite.dst.y = t.position.y;

                // If entity has animation, update src rect
                if (entity->hasComponent<Animation>())
                {
                    auto &animation = entity->getComponent<Animation>();
                    sprite.src = animation.clips[animation.currentClip].frameIndices[animation.currentFrame];
                }

                TextureManager::draw(sprite.texture, sprite.src, sprite.dst);
            }
        }
    }
};