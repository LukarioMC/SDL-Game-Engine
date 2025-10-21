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
#include "SpawnTimerSystem.h"
#include "DestructionSystem.h"

class World
{
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;
    AnimationSystem animationSystem;
    CameraSystem cameraSystem;
    CollisionSystem collisionSystem;
    DestructionSystem destructionSystem;
    KeyboardInputSystem keyboardInputSystem;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    SpawnTimerSystem spawnTimerSystem;
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
        spawnTimerSystem.update(entities, dt);
        destructionSystem.update(entities);
        synchronizeEntities();
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

    Entity &createDeferredEntity()
    {
        deferredEntities.emplace_back(std::make_unique<Entity>());
        return *deferredEntities.back();
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

    void synchronizeEntities()
    {
        if (deferredEntities.empty())
            return;
        // Move deferred entities into the active entities list & clear it
        std::move(deferredEntities.begin(), deferredEntities.end(), std::back_inserter(entities));
        deferredEntities.clear();
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