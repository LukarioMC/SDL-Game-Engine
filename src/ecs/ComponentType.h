#pragma once
#include <cstddef>

// Creating a type alias for std::size_t; used to repr sizes and indices, unsigned and very large (long long)
using ComponentTypeID = std::size_t;

// When you have a free function and defined in a header, each .cpp file that
// includes this header would get it's own definition causing a linker error.
// Using inline merges them into one definiton. Returns a unique number every
// time we call it. id is static to it maintains it's value over multiple calls.
inline ComponentTypeID getComponentTypeID()
{
    static ComponentTypeID id = 0;
    return id++;
}

// Overloaded function with slightly different signature.
// Template allows us to use generic types & by default is inline.
//
// e.g. getComponentTypeID<Position>() -> Always returns 0, for example.
// getComponentTypeID<Health>() -> Always returns 1
// This is because it's a static local variable that is initialized once.
template <typename T>
ComponentTypeID getComponentTypeID()
{
    static ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}