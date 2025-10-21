#include <Game.h>
#include <World.h>
#include <iostream>

void printCollisionEvent(const CollisionEvent &collision)
{
    Collider colliderA = collision.entityA->getComponent<Collider>();
    Collider colliderB = collision.entityB->getComponent<Collider>();
    std::cout << "A collision occurred between " << colliderA.tag << " and " << colliderB.tag << std::endl;
}

void World::playerWallCollisionHandler(const CollisionEvent &collision)
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

void World::playerItemCollisionHandler(const CollisionEvent &collision)
{
    if (!isValidCollision(collision))
        return;

    auto &colliderA = collision.entityA->getComponent<Collider>();
    auto &colliderB = collision.entityB->getComponent<Collider>();

    Entity *sceneStateEntity = nullptr;
    for (auto &e : entities)
    {
        if (e->hasComponent<SceneState>())
        {
            sceneStateEntity = e.get();
            break;
        }
    }

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
        // Increment score in scene state
        if (!sceneStateEntity)
            return;
        auto &sceneState = sceneStateEntity->getComponent<SceneState>();
        sceneState.coinsCollected++;
        if (sceneState.coinsCollected >= 2)
        {
            Game::onSceneChangeRequest("level2");
        }
    }
}

void World::playerProjectileCollisionHandler(const CollisionEvent &collision)
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
        Game::onSceneChangeRequest("gameover");
    }
}

World::World()
{
    eventManager.subscribe([&](const CollisionEvent &e)
                           { playerWallCollisionHandler(e); });
    eventManager.subscribe([&](const CollisionEvent &e)
                           { playerItemCollisionHandler(e); });
    eventManager.subscribe([&](const CollisionEvent &e)
                           { playerProjectileCollisionHandler(e); });
    // eventManager.subscribe(printCollisionEvent);
    // eventManager.subscribe<CollisionEvent>(playerWallCollisionHandler);
    // eventManager.subscribe<CollisionEvent>(playerItemCollisionHandler);
    // eventManager.subscribe<CollisionEvent>(playerProjectileCollisionHandler);
    // eventManager.subscribe<CollisionEvent>(printCollisionEvent);
}