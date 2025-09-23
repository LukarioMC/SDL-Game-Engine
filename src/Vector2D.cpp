#include "Vector2D.h"
#include <cmath>

Vector2D &Vector2D::normalize()
{
    float length = sqrt(x * x + y * y);
    if (length > 0)
    {
        this->x /= length;
        this->y /= length;
    }
    return *this;
}

// Allows us to add two vectors whilst assigning the result to the left's values
Vector2D &Vector2D::operator+=(const Vector2D &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

// Allows us to mult Vector2D from left-hand side
Vector2D Vector2D::operator*(float scaler) const
{
    return Vector2D(x * scaler, y * scaler);
}

// Allows us to mult Vector2D from right-hand side
Vector2D operator*(float scaler, Vector2D vec)
{
    return Vector2D(vec.x * scaler, vec.y * scaler);
}