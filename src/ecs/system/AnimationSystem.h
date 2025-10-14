#pragma once

#include <memory>

#include "AnimationClip.h"
#include "Component.h"
#include "Entity.h"

// State System: Determine which clip to use
// Also check if the animation has been switched
// Playback System: Advances animations

class AnimationSystem
{
public:
    void update(const std::vector<std::unique_ptr<Entity>> &entities, float dt)
    {
        for (auto &e : entities)
        {
            if (e->hasComponent<Animation>() && e->hasComponent<Velocity>())
            {
                auto &animation = e->getComponent<Animation>();
                auto &velocity = e->getComponent<Velocity>();

                // State system
                std::string newClip;
                // Hardcoded for now.
                if (velocity.direction.x > 0.0f)
                {
                    newClip = "walk_right";
                }
                else if (velocity.direction.x < 0.0f)
                {
                    newClip = "walk_left";
                }
                else
                {
                    newClip = "idle_right";
                }

                // Check if animation has switched and reset associated vars
                if (newClip != animation.currentClip)
                {
                    animation.currentClip = newClip;
                    animation.time = 0.0f;
                    animation.currentFrame = 0;
                }

                // Playback system
                float animationframeSpeed = animation.speed;         // How long each animation frame lasts
                auto &clip = animation.clips[animation.currentClip]; // Get animation frame data
                animation.time += dt;                                // Advance time every game loop frame

                if (animation.time > animationframeSpeed)
                {
                    // Enough time passed, advance frame
                    animation.time -= animationframeSpeed;
                    std::size_t totalFrames = clip.frameIndices.size();
                    animation.currentFrame = (animation.currentFrame + 1) % totalFrames;
                }
            }
        }
    }
};
