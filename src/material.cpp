#include "material.hpp"

#include "linalg/random.hpp"


Material::Material(const RGBPixel &_color): color(_color) {}


MirrorMaterial::MirrorMaterial(const RGBPixel &_color, const float _noise):
    Material(_color), noise_coef((0.f <= _noise && _noise < 1.f) ? _noise : 0.f)
{}

Vector3 MirrorMaterial::reflect(const Vector3 &direction, const Vector3 &normal) const
{
    Vector3 shift{
        random_frac(), random_frac(), random_frac()
    };
    return direction + direction.project(normal) * 2 + shift * this->noise_coef;
}
