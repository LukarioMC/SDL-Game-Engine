#pragma once
#include <array>
#include <bitset>
#include <cstddef>

#include "ComponentType.h"

// Create a const that is evaluated at compiletime (constexpr)
// 32 components fits perfectly within a 32-bit integer
constexpr std::size_t MAX_COMPONENTS = 32;

// Bitsets are arrays of bits (e.g. bitset[0] = 1); quite efficient.
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

// Using a fixed-size array where each index is a component. Index corresponds to the ComponentTypeID
// We use a fixed number of components so there's no dynamic allocation for the array.
using ComponentArray = std::array<void *, MAX_COMPONENTS>;

class Entity
{
    bool active = true;
    ComponentArray componentArray{};
    ComponentBitSet componentBitSet{};

public:
    bool isActive()
    {
        return active;
    }
    void destroy()
    {
        active = false;
    }

    // Templates need impl in header (e.g. entity.hasComponent<Position>() -> T/F)
    template <typename T>
    bool hasComponent()
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    // Template that can recieve many arguments
    template <typename T, typename... mArgs>
    T &addComponent(mArgs &&...args)
    {
        // Implements "perfect forwarding", everything not treated as an lvalue
        // More efficient with moves and temporaries
        T *component(new T(std::forward<mArgs>(args)...));

        componentArray[getComponentTypeID<T>()] = component;
        componentBitSet[getComponentTypeID<T>()] = true;

        return *component;
    }

    template <typename T>
    T &getComponent()
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        // Static cast to type rather than returning void*
        return *static_cast<T *>(ptr);
    }

    template <typename T>
    void deactivateComponent()
    {
        componentBitSet[getComponentTypeID<T>()] = false;
    }
};