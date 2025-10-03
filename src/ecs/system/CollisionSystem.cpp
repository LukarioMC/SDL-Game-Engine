#include "World.h"
#include <Collision.h>
#include "CollisionSystem.h"
#include <iostream>

void CollisionSystem::update(World &world)
{
    // Get list of entities w/ collliders.
    const std::vector<Entity *> collidables = queryCollidables(world.getEntities());
    // Outer loop
    for (size_t i = 0; i < collidables.size(); i++)
    {
        auto entityA = collidables[i];
        auto &transformA = entityA->getComponent<Transform>();
        auto &colliderA = entityA->getComponent<Collider>();

        colliderA.rect.x = transformA.position.x;
        colliderA.rect.y = transformA.position.y;
        // Check for collision interaction
        for (size_t j = i + 1; j < collidables.size(); j++)
        {
            auto entityB = collidables[j];
            auto &colliderB = entityB->getComponent<Collider>();

            if (Collision::AABB(colliderA, colliderB))
            {
                std::cout << colliderA.tag << " hit " << colliderB.tag << std::endl;
                world.getEventManager().emit(CollisionEvent{entityA, entityB});
            }
        }
    }
}

std::vector<Entity *> CollisionSystem::queryCollidables(const std::vector<std::unique_ptr<Entity>> &entities)
{
    std::vector<Entity *> collidables;
    for (auto &e : entities)
    {
        if (e->hasComponent<Transform>() && e->hasComponent<Collider>())
        {
            collidables.push_back(e.get());
        }
    }
    return collidables;
}