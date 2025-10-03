#pragma once
#include <vector>
#include <memory>

#include "Entity.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "KeyboardInputSystem.h"
#include "CollisionSystem.h"

class World
{
    std::vector<std::unique_ptr<Entity>> entities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;

public:
    void update(float dt, const SDL_Event &event)
    {
        keyboardInputSystem.update(entities, event);
        movementSystem.update(entities, dt);
        collisionSystem.update(*this);
        cleanup();
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