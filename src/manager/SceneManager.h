#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <Scene.h>

struct SceneParams
{
    const char *name;
    const char *mapPath;
    int windowWidth;
    int windowHeight;
};

class SceneManager
{
private:
    std::unordered_map<std::string, SceneParams> sceneParams;
    std::string pendingScene;
    void changeScene(const std::string &name)
    {
        auto it = sceneParams.find(name);
        if (it != sceneParams.end())
        {
            const auto &params = it->second;
            std::string name(params.name);
            std::string path(params.mapPath);
            // Create the scene we are changing to
            currentScene = std::make_unique<Scene>(params.name, params.mapPath, params.windowWidth, params.windowHeight);
        }
        else
        {
            std::cerr << "Scene \"" << name << "\" not found!" << std::endl;
        }
    }

public:
    std::unique_ptr<Scene> currentScene;
    void loadScene(const char *sceneName, const char *mapPath, const int windowWidth, const int windowHeight)
    {
        std::string name(sceneName);
        std::string path(mapPath);
        sceneParams[sceneName] = {sceneName, mapPath, windowWidth, windowHeight};
    }

    void changeSceneDeferred(const std::string &name)
    {
        pendingScene = name;
    }

    void update(const float dt, const SDL_Event &e)
    {
        if (currentScene)
            currentScene->update(dt, e);
        if (!pendingScene.empty())
        {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() const
    {
        if (currentScene)
            currentScene->render();
    }
};
