#pragma once

class World; // "Forward declare" the class, we don't need all of it

class CollisionSystem
{
public:
    void update(World &world);

private:
    std::vector<Entity *> queryCollidables(const std::vector<std::unique_ptr<Entity>> &entities);
};
