#pragma once

#include <string>
#include <unordered_map>
#include "Component.h"

class AssetManager
{
private:
    static std::unordered_map<std::string, Animation> animations;
    static Animation loadAnimationFromXML(const char *path);

public:
    static void loadAnimation(const std::string &clipName, const char *path);
    static const Animation &getAnimation(const std::string &clipName);
};
