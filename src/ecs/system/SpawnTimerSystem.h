#pragma once

#include <memory>
#include <vector>

#include <Entity.h>
#include <Component.h>

class SpawnTimerSystem
{
public:
    void update(const std::vector<std::unique_ptr<Entity>> &entities, const float dt)
    {
        for (auto &entity : entities)
        {
            if (entity->hasComponent<TimedSpawner>())
            {
                auto &spawner = entity->getComponent<TimedSpawner>();

                spawner.timer -= dt;
                if (spawner.timer <= 0)
                {
                    spawner.timer = spawner.spawnInterval; // Reset timer
                    spawner.spawnCallback();               // Create new entity
                }
            }
        }
    }
};
