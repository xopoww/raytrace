#pragma once

//
// Bodies that can be in a scene
//

#include "linalg/ray.hpp"

#include <utility>

// Basic interface for 3D shapes that rays can intersect
class Object
{
public:

    // Get the intersections of ray with the body.
    //
    // Intersections are represented as a ray from the point of intersection
    // in the direction normal to the surface of the body in that point. The
    // direction of the ray is chosen so that its dot product with the direction
    // of the original ray is negative (i.e. the returned ray looks outwards for
    // the first intersection and inwards for the second one).
    //
    // Two intersections are computed: the first one is where the ray enters
    // the body and the second one is where it leaves. For more complex bodies
    // where more than two intersections are possible two closest to ray.origin
    // are returned.
    //
    // If there is only one (tangent) intersection, both returned rays will 
    // represent it. If there are no intersections, both returned rays will
    // have an infinite vector as their origin.
    virtual std::pair<Ray, Ray> intersect(const Ray &ray) const = 0;

    // Determine if the point is inside the body (returns true if the point is
    // on the surface of the body).
    virtual bool is_in(const Vector3 &point) const = 0;
};


class Sphere : public Object
{
    coord_t radius;

    Vector3 center;

public:

    Sphere() = delete;
    Sphere(const Sphere &) = default;

    Sphere(const coord_t _radius, const Vector3 &_center);

    std::pair<Ray, Ray> intersect(const Ray &ray) const override;

    bool is_in(const Vector3 &point) const override;
};


#include "material.hpp"

#include <memory>

class Body
{
    std::shared_ptr<Object> obj;
    Material material;

public:

    Body() = delete;
    Body(const Body &) = default;

    Body(std::shared_ptr<Object> _obj, const Material &_material);

    friend struct Camera;
};
