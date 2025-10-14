#include "world.h"
#include <iostream>

void printCollisionEvent(const CollisionEvent &collision)
{
    Collider colliderA = collision.entityA->getComponent<Collider>();
    Collider colliderB = collision.entityB->getComponent<Collider>();
    std::cout << "A collision occurred between " << colliderA.tag << " and " << colliderB.tag << std::endl;
}

World::World()
{
    eventManager.subscribe<CollisionEvent>([](const CollisionEvent &collision)
                                           {
                                               if (collision.entityA == nullptr || collision.entityB == nullptr)
                                                   return;
                                               if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>()))
                                                   return;
                                               auto &colliderA = collision.entityA->getComponent<Collider>();
                                               auto &colliderB = collision.entityB->getComponent<Collider>();

                                               Entity *player = nullptr;
                                               Entity *item = nullptr;
                                               Entity *wall = nullptr;

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
                                               if (player && wall)
                                               {
                                                   // Stop player movement
                                                   auto &t = player->getComponent<Transform>();
                                                   t.position = t.oldPosition;
                                               } });

    eventManager.subscribe<CollisionEvent>(printCollisionEvent);
}