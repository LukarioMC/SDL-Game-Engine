
#pragma once

class Vector2D
{
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2D()
    {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2D(float x, float y) : x(x), y(y) {}
};