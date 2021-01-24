#include "body.hpp"

#include <cmath>

Sphere::Sphere(const coord_t _radius, const Vector3 &_center):
    radius(_radius), center(_center)
{}

std::pair<Ray, Ray> Sphere::intersect(const Ray &ray) const
{
    coord_t
        a = std::pow(ray.direction.length(), 2),
        b = 2 * (ray.origin - this->center).dot(ray.direction),
        c = std::pow((ray.origin - this->center).length(), 2) - std::pow(this->radius, 2);
    
    auto roots = solve_quadratic(a, b, c);

    if (roots.first <= 0)
    {
        roots.first = infinity;
    }
    if (roots.second <= 0)
    {
        roots.second = infinity;
    }
    
    // if (!(std::isinf(roots.first) && std::isinf(roots.second)))
    // {
    //     std::cout << a << " " << b << " " << c << std::endl;
    //     std::cout << roots.first << "  " << roots.second << std::endl;
    // }

    Vector3 i1 = ray.advance(roots.first), i2 = ray.advance(roots.second);

    return {
        {i1, i1 - this->center},
        {i2, this->center - i2}
    };
}

bool Sphere::is_in(const Vector3 &point) const
{
    return (point - this->center).length() <= this->radius;
}


Body::Body(std::shared_ptr<Object> _obj, std::shared_ptr<Material> _material):
    obj(_obj), material(_material)
{}
