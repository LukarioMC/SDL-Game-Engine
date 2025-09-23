#pragma once
#include <vector>
#include <memory>

#include "Entity.h"
#include "MovementSystem.h"
#include "RenderSystem.h"

class World
{
    std::vector<std::unique_ptr<Entity>> entities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;

public:
    void update(float dt)
    {
        movementSystem.update(entities, dt);
    }
    void render()
    {
        renderSystem.render(entities);
    }

    Entity &createEntity()
    {
        // Use emplace instead of push so we don't copy.
        entities.emplace_back(std::make_unique<Entity>());
        return *entities.back();
    }

    std::vector<std::unique_ptr<Entity>> &getEntities()
    {
        return entities;
    }

    void cleanup()
    {
        // Use lambda predicate to manage and remove inactive entities.
        std::erase_if(entities, [](std::unique_ptr<Entity> &e)
                      { return !e->isActive(); });
    }
};