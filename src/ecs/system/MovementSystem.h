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
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>())
            {
                auto &t = entity->getComponent<Transform>();
                auto v = entity->getComponent<Velocity>();
                Vector2D direction = v.direction;
                // Normalize
                direction.normalize();
                // We need an overloaded operator function
                Vector2D velocity = direction * v.speed;
                t.position += (velocity * dt);
            }
        }
    }
};