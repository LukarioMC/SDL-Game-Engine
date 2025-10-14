#pragma once
#include <vector>
#include <memory>

#include "Entity.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "KeyboardInputSystem.h"
#include "CollisionSystem.h"
#include "EventManager.h"
#include "Map.h"
#include "AnimationSystem.h"
#include "CameraSystem.h"

class World
{
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    CameraSystem cameraSystem;
    AnimationSystem animationSystem;
    EventManager eventManager;

public:
    World();

    void update(float dt, const SDL_Event &event)
    {
        keyboardInputSystem.update(entities, event);
        movementSystem.update(entities, dt);
        collisionSystem.update(*this);
        animationSystem.update(entities, dt);
        cameraSystem.update(entities);
        cleanup();
    }

    void render()
    {
        for (auto &e : entities)
        {
            if (e->hasComponent<Camera>())
            {
                map.draw(e->getComponent<Camera>());
                break;
            }
        }
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

    EventManager &getEventManager()
    {
        return eventManager;
    }

    Map &getMap()
    {
        return map;
    }
};