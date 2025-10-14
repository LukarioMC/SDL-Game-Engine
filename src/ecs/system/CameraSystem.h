#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include <Component.h>

class CameraSystem
{
public:
    void update(const std::vector<std::unique_ptr<Entity>> &entities)
    {
        Entity *playerEntity;

        for (auto &e : entities)
        {
            if (e->hasComponent<PlayerTag>())
            {
                playerEntity = e.get();
                break;
            }
        }

        if (!playerEntity)
            return;

        auto &playerTransform = playerEntity->getComponent<Transform>();

        for (auto &e : entities)
        {
            if (e->hasComponent<Camera>())
            {
                auto &cam = e->getComponent<Camera>();
                cam.view.x = playerTransform.position.x - cam.view.w / 2;
                cam.view.y = playerTransform.position.y - cam.view.h / 2;

                // Clamp to within world bounds. Player can still walk off-screen.
                if (cam.view.x < 0)
                {
                    cam.view.x = 0;
                }
                if (cam.view.y < 0)
                {
                    cam.view.y = 0;
                }
                if (cam.view.x > cam.worldWidth - cam.view.w)
                {
                    cam.view.x = cam.worldWidth - cam.view.w;
                }
                if (cam.view.y > cam.worldHeight - cam.view.h)
                {
                    cam.view.y = cam.worldHeight - cam.view.h;
                }
            }
        }
    }
};
