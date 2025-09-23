
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

    Vector2D &normalize();

    // Allows us to add two vectors, returns left Vector modified
    Vector2D &operator+=(const Vector2D &vec);
    // Member operator function. Allows for Vec2D * float
    Vector2D operator*(float scaler) const;
    // Make a non-member function "friend" to allow float * Vec2D (reversed)
    friend Vector2D operator*(float scaler, Vector2D &vec);
};