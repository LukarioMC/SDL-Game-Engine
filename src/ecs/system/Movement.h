#pragma once
#include <vector>
#include <memory>

#include "Component.h"
#include "Entity.h"

class MovementSystem
{
public:
    void update(std::vector<std::unique_ptr<Entity>> &entities, float dt)
    {
        for (auto &entity : entities)
        {
            if (entity->hasComponent<Position>())
            {
                auto &position = entity->getComponent<Position>();
                position.x += 60 * dt;
                position.y += 60 * dt;
            }
        }
    }
};