#include "ray.hpp"

Ray::Ray(const Vector3 &_origin, const Vector3 &_direction):
origin(_origin), direction(_direction.norm())
{}

Vector3 Ray::advance(const coord_t t) const
{
    return this->origin + this->direction * t;
}
