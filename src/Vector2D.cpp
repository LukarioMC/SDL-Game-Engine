#include "Vector2D.h"
#include <cmath>

// Returns this vector normalized (total length/magnitude is 1)
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

// Addition of two vectors, returns the new result
Vector2D Vector2D::operator+(const Vector2D &vec) const
{
    return Vector2D(this->x + vec.x, this->y + vec.y);
}

// Subtraction of two vectors, returns the new result
Vector2D Vector2D::operator-(const Vector2D &vec) const
{
    return Vector2D(this->x - vec.x, this->y - vec.y);
}

// Multiplication of vector & scaler, returns the new result
Vector2D Vector2D::operator*(float scaler) const
{
    return Vector2D(this->x * scaler, this->y * scaler);
}

// Division of two vector & scaler, returns the new result
Vector2D Vector2D::operator/(float scaler) const
{
    return Vector2D(this->x / scaler, this->y / scaler);
}

// Add two vectors, & assign the result to the left vector
Vector2D &Vector2D::operator+=(const Vector2D &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

// Subtract two vectors, & assign the result to the left vector
Vector2D &Vector2D::operator-=(const Vector2D &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}

// Allows us to mult Vector2D from left-hand side
Vector2D &Vector2D::operator*=(float scaler)
{
    this->x *= scaler;
    this->y *= scaler;
    return *this;
}

// Allows us to mult Vector2D from left-hand side
Vector2D &Vector2D::operator/=(float scaler)
{
    this->x /= scaler;
    this->y /= scaler;
    return *this;
}

bool Vector2D::operator==(const Vector2D &vec)
{
    // TODO: Look into float comparisons
    return this->x == vec.x && this->y == vec.y;
}

bool Vector2D::operator!=(const Vector2D &vec)
{
    // TODO: Look into float comparisons
    return this->x != vec.x && this->y != vec.y;
}

// ----------------------------
// Non-member function(s) "friend"s
// ----------------------------

// Allows us to mult Vector2D from right-hand side
Vector2D operator*(float scaler, const Vector2D &vec)
{
    return Vector2D(vec.x * scaler, vec.y * scaler);
}

Vector2D operator-(const Vector2D &vec)
{
    return Vector2D(-vec.x, -vec.y);
}