#pragma once

#include <string>
#include <SDL3/SDL_events.h>

#include <Vector2D.h>
#include <World.h>

class Scene
{
private:
    std::string name;
    void createProjectile(Vector2D pos, Vector2D dir, int speed);

public:
    World world;

    Scene(const char *sceneName, const char *mapPath, const int windowWidth, const int windowHeight);

    void update(const float dt, const SDL_Event &e)
    {
        world.update(dt, e);
    }

    void render()
    {
        world.render();
    }

    const std::string &getName() const
    {
        return name;
    }
};
