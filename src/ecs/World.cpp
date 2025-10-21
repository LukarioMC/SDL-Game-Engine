#include "world.h"
#include <iostream>

void printCollisionEvent(const CollisionEvent &collision)
{
    Collider colliderA = collision.entityA->getComponent<Collider>();
    Collider colliderB = collision.entityB->getComponent<Collider>();
    std::cout << "A collision occurred between " << colliderA.tag << " and " << colliderB.tag << std::endl;
}

bool isValidCollision(const CollisionEvent &collision)
{
    if (collision.entityA == nullptr || collision.entityB == nullptr)
        return false;
    if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>()))
        return false;
    // Both entities exist and have collider components
    return true;
}

void playerWallCollisionHandler(const CollisionEvent &collision)
{
    if (!isValidCollision(collision))
        return;
    auto &colliderA = collision.entityA->getComponent<Collider>();
    auto &colliderB = collision.entityB->getComponent<Collider>();

    Entity *player = nullptr;
    Entity *wall = nullptr;

    if (colliderA.tag == "player" && colliderB.tag == "wall")
    {
        player = collision.entityA;
        wall = collision.entityB;
    }
    else if (colliderA.tag == "wall" && colliderB.tag == "player")
    {
        player = collision.entityB;
        wall = collision.entityA;
    }
    // Check if the player and a wall collided & stop player movement
    if (player && wall)
    {
        auto &t = player->getComponent<Transform>();
        t.position = t.oldPosition;
    }
}

void playerItemCollisionHandler(const CollisionEvent &collision)
{
    if (!isValidCollision(collision))
        return;
    auto &colliderA = collision.entityA->getComponent<Collider>();
    auto &colliderB = collision.entityB->getComponent<Collider>();

    Entity *player = nullptr;
    Entity *item = nullptr;

    if (colliderA.tag == "player" && colliderB.tag == "item")
    {
        player = collision.entityA;
        item = collision.entityB;
    }
    else if (colliderA.tag == "item" && colliderB.tag == "player")
    {
        player = collision.entityB;
        item = collision.entityA;
    }

    if (player && item)
    {
        item->destroy();
    }
}

void playerProjectileCollisionHandler(const CollisionEvent &collision)
{
    if (!isValidCollision(collision))
        return;
    auto &colliderA = collision.entityA->getComponent<Collider>();
    auto &colliderB = collision.entityB->getComponent<Collider>();

    Entity *player = nullptr;
    Entity *projectile = nullptr;

    if (colliderA.tag == "player" && colliderB.tag == "projectile")
    {
        player = collision.entityA;
        projectile = collision.entityB;
    }
    else if (colliderA.tag == "projectile" && colliderB.tag == "player")
    {
        player = collision.entityB;
        projectile = collision.entityA;
    }

    if (player && projectile)
    {
        player->destroy();
    }
}

World::World()
{
    eventManager.subscribe<CollisionEvent>(playerWallCollisionHandler);
    eventManager.subscribe<CollisionEvent>(playerItemCollisionHandler);
    eventManager.subscribe<CollisionEvent>(playerProjectileCollisionHandler);
    eventManager.subscribe<CollisionEvent>(printCollisionEvent);
}