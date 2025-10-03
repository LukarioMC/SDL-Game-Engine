#include "Collision.h"

bool Collision::AABB(const SDL_FRect &rectA, const SDL_FRect &rectB)
{
    // 1. Check if right edge of A >= left edge of B
    bool rightEdgeOverlapsB = rectA.x + rectA.w >= rectB.x;
    // 2. Check if right edge of B >= left edge of A
    bool rightEdgeOverlapsA = rectB.x + rectB.w >= rectA.x;
    // 3. Check if bottom edge of A >= top edge of B
    bool topEdgeOverlapsA = rectA.y + rectA.h >= rectB.y;
    // 4. Check if bottom edge of B >= top edge of A
    bool topEdgeOverlapsB = rectB.y + rectB.h >= rectA.y;

    return rightEdgeOverlapsA && rightEdgeOverlapsB && topEdgeOverlapsA && topEdgeOverlapsB;
}

bool Collision::AABB(const Collider &colA, const Collider &colB)
{
    return AABB(colA.rect, colB.rect);
}