#pragma once
#include "Entity.h"
#include <functional>

struct CollisionEvent
{
    Entity *entityA = nullptr;
    Entity *entityB = nullptr;
};

// Uses observer pattern
class EventManager
{
public:
    template <typename EventType>
    void emit(const EventType &event)
    {
        // Retrieve subscribed entities
        auto &listeners = getListeners<EventType>();
        for (auto &listener : listeners)
        {
            listener(event); // Invoke the function
        }
    }

    template <typename EventType>
    void subscribe(std::function<void(const EventType &)> callback)
    {
        // Pass callable wrapper to the list of subscribers
        getListeners<EventType>().push_back(callback);
    }

private:
    // Each event type stores its own vector o listeners without explicit management through local static var
    template <typename EventType>
    std::vector<std::function<void(const EventType &)>> &getListeners()
    {
        static std::vector<std::function<void(const EventType &)>> listeners;
        return listeners;
    }
};