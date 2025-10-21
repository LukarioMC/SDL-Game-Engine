#pragma once

#include <ostream>
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

    // ----------------------------
    // Member operator function(s)
    // ----------------------------

    // Addition/subtraction/Multiplication/division, returns new vector
    Vector2D operator+(const Vector2D &vec) const;
    Vector2D operator-(const Vector2D &vec) const;
    Vector2D operator*(float scaler) const;
    Vector2D operator/(float scaler) const;
    // Add/subtract/multiply/divide two vectors, returns left vector modified
    Vector2D &operator+=(const Vector2D &vec);
    Vector2D &operator-=(const Vector2D &vec);
    Vector2D &operator*=(float scaler);
    Vector2D &operator/=(float scaler);
    // Equality of vectors
    bool operator==(const Vector2D &vec);
    bool operator!=(const Vector2D &vec);

    // ----------------------------
    // Non-member function(s) "friend"
    // ----------------------------

    // Allows float * Vec2D (reversed multiplication)
    friend Vector2D operator*(float scaler, const Vector2D &vec);
    // Allows -v (flips direction)
    friend Vector2D operator-(const Vector2D &vec);

    // Allows for printing
    friend std::ostream &operator<<(std::ostream &cout, const Vector2D &vec)
    {
        cout << "Vector2D{ X:" << vec.x << ", Y:" << vec.y << "};";
        return cout;
    }
};