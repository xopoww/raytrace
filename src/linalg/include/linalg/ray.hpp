#pragma once

//
// (TODO: probably move to vector.hpp)
//

#include "linalg/vector.hpp"

// Ray (or pinned vector) represents a 3D vector from a fixed point (origin)
struct Ray
{
    Vector3 origin;
    Vector3 direction;

    Ray(const Vector3 &_origin, const Vector3 &_direction);

    Ray(const Ray &) = default;

    Vector3 advance(const coord_t t) const;
};
