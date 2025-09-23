#pragma once
#include <memory>
#include <vector>
#include <SDL3/SDL_events.h>

#include "Component.h"
#include "Entity.h"

class KeyboardInputSystem
{
public:
    void update(const std::vector<std::unique_ptr<Entity>> &entities, const SDL_Event &event)
    {
        for (auto &entity : entities)
        {
            if (entity->hasComponent<Velocity>())
            {
                // MovementSystem handles actual movement, simply change direction.
                auto &v = entity->getComponent<Velocity>();
                if (event.type == SDL_EVENT_KEY_DOWN)
                {
                    switch (event.key.key)
                    {
                    case SDLK_W:
                        v.direction.y = -1;
                        break;
                    case SDLK_A:
                        v.direction.x = -1;
                        break;
                    case SDLK_S:
                        v.direction.y = 1;
                        break;
                    case SDLK_D:
                        v.direction.x = 1;
                        break;

                    default:
                        break;
                    }
                }
                else if (event.type == SDL_EVENT_KEY_UP)
                {
                    switch (event.key.key)
                    {
                    case SDLK_W:
                    case SDLK_S:
                        v.direction.y = 0;
                        break;
                    case SDLK_A:
                    case SDLK_D:
                        v.direction.x = 0;
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }
};