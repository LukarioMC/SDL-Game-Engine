#include <Scene.h>
#include <AssetManager.h>

Scene::Scene(const char *sceneName, const char *mapPath, const int windowWidth, const int windowHeight) : name(sceneName)
{
    world.getMap().load(mapPath, TextureManager::load("../asset/spritesheet_terrain.png"));
    // Add entities
    for (auto &collider : world.getMap().colliders)
    {
        auto &e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto &c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        SDL_Texture *tex = TextureManager::load("../asset/spritesheet_terrain.png");
        SDL_FRect colSrc{0, 32, 32, 32};
        SDL_FRect colDst{c.rect.x, c.rect.y, c.rect.w, c.rect.h};
        e.addComponent<Sprite>(tex, colSrc, colDst);
    }

    // Create Camera
    auto &camera = world.createEntity();
    SDL_FRect cameraView{};
    cameraView.w = windowWidth;
    cameraView.h = windowHeight;
    camera.addComponent<Camera>(cameraView, world.getMap().width * 32, world.getMap().height * 32); // ? Hardcoded w/h

    // Player
    auto &player(world.createEntity());
    auto &playerTransform = player.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);
    auto &playerVelocity = player.addComponent<Velocity>(Vector2D(0, 0), 400.0f);

    Animation animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture *playerTex = TextureManager::load("../asset/animations/chick_anim.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0];
    SDL_FRect playerDst{playerTransform.position.x, playerTransform.position.y, 64, 64};

    // SDL_Texture *playerTex = TextureManager::load("../asset/mario.png");
    // SDL_FRect playerSrc{0, 0, 32, 44};
    // SDL_FRect playerDst{playerTransform.position.x, playerTransform.position.y, 64, 88};

    player.addComponent<Sprite>(playerTex, playerSrc, playerDst);

    auto &playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    player.addComponent<PlayerTag>();

    // Coin Items
    for (auto point : world.getMap().itemSpawns)
    {
        auto &item(world.createEntity());
        auto &itemTransform = item.addComponent<Transform>(Vector2D(point.x - 16, point.y - 16), 0.0f, 1.0f);

        SDL_Texture *itemTex = TextureManager::load("../asset/coin.png");
        SDL_FRect itemSrc{0, 0, 32, 32};
        SDL_FRect itemDst{itemTransform.position.x, itemTransform.position.y, 32, 32};
        item.addComponent<Sprite>(itemTex, itemSrc, itemDst);

        auto &itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDst.w;
        itemCollider.rect.h = itemDst.h;
    }

    // TimedSpawner
    auto &spawner(world.createEntity());
    Transform t = spawner.addComponent<Transform>(Vector2D(windowWidth / 2, windowHeight - 5), 0.0f, 1.0f);
    spawner.addComponent<TimedSpawner>(2.0f, [this, t]
                                       {
                                           // Create enemy
                                           auto &e(world.createDeferredEntity());
                                           e.addComponent<Transform>(Vector2D(t.position.x, t.position.y), 0.0f, 1.0f);
                                           e.addComponent<Velocity>(Vector2D(0, -1), 100.0f);

                                           SDL_Texture *tex = TextureManager::load("../asset/animations/bird_anim.png");
                                           SDL_FRect src{0, 0, 32, 32};
                                           SDL_FRect dst{t.position.x, t.position.y, 32, 32};
                                           e.addComponent<Sprite>(tex, src, dst);

                                           Animation anim = AssetManager::getAnimation("enemy");
                                           e.addComponent<Animation>(anim);

                                           Collider c = e.addComponent<Collider>("projectile");
                                           c.rect.w = dst.w;
                                           c.rect.h = dst.h;

                                           e.addComponent<ProjectileTag>(); });

    // Add scene state component
    auto &state(world.createEntity());
    state.addComponent<SceneState>();
}