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
        // Setup camera
        Entity *cameraEntity = nullptr;
        for (auto &e : entities)
        {
            if (e->hasComponent<Camera>())
            {
                cameraEntity = e.get();
                break;
            }
        }

        if (!cameraEntity)
            return; // No camera, no rendering
        auto &camera = cameraEntity->getComponent<Camera>();

        for (auto &entity : entities)
        {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>())
            {
                auto &transform = entity->getComponent<Transform>();
                auto &sprite = entity->getComponent<Sprite>();

                // Convert entities from "world space" to "screen space"
                sprite.dst.x = transform.position.x - camera.view.x;
                sprite.dst.y = transform.position.y - camera.view.y;

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