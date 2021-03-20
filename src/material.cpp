#include "material.hpp"

#include "linalg/random.hpp"


Material::Material(const RGBPixel &_color): color(_color) {}


MirrorMaterial::MirrorMaterial(const RGBPixel &_color, const float _noise):
    Material(_color), noise_coef((0.f <= _noise && _noise < 1.f) ? _noise : 0.f)
{}

Ray MirrorMaterial::scatter(const Ray &incident, const Ray &normal) const
{
    Vector3 shift{
        random_frac(), random_frac(), random_frac()
    };
    Vector3 reflected = incident.direction + incident.direction.project(normal.direction) * 2 + shift * this->noise_coef;

    return {normal.origin, reflected};
}


DiffuseMaterial::DiffuseMaterial(const RGBPixel &_color, const float reflect_prob):
    Material(_color), ref_p((0.f <= reflect_prob && reflect_prob < 1.f) ? reflect_prob : 0.f)
{
}

Ray DiffuseMaterial::scatter(const Ray &incident, const Ray &normal) const
{
    Vector3 shift{
        random_frac(), random_frac(), random_frac()
    };
    Vector3 target = normal.origin + normal.direction + shift;
    if (target == normal.origin)
    {
        target = normal.origin + normal.direction;
    }

    return {normal.origin, (target - normal.origin)};
}