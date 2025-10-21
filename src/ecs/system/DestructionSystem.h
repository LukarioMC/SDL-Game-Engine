#pragma once

#include <vector>
#include <memory>

#include <Entity.h>
#include <Component.h>

class DestructionSystem
{
public:
    void update(const std::vector<std::unique_ptr<Entity>> &entities)
    {
        Entity *cameraEntity = nullptr;

        for (auto &entity : entities)
        {
            if (entity->hasComponent<Camera>())
            {
                cameraEntity = entity.get();
                break;
            }
        }

        if (!cameraEntity)
            return;
        auto &camera = cameraEntity->getComponent<Camera>();

        for (auto &entity : entities)
        {
            if (entity->hasComponent<ProjectileTag>() && entity->hasComponent<Transform>())
            {
                auto &transform = entity->getComponent<Transform>();

                bool pastRightScreenEdge = transform.position.x > (camera.view.x + camera.view.w);
                bool pastLeftScreenEdge = transform.position.x < camera.view.x;
                bool pastBottomScreenEdge = transform.position.y > (camera.view.y + camera.view.h);
                bool pastTopScreenEdge = transform.position.y < camera.view.y;

                if (pastRightScreenEdge || pastLeftScreenEdge || pastBottomScreenEdge || pastTopScreenEdge)
                {
                    entity->destroy();
                }
            }
        }
    }
};
