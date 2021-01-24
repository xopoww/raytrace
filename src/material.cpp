#include "material.hpp"


Material::Material(const RGBPixel &_color): color(_color) {}


MirrorMaterial::MirrorMaterial(const RGBPixel &_color): Material(_color) {}

Vector3 MirrorMaterial::reflect(const Vector3 &direction, const Vector3 &normal) const
{
    return direction + direction.project(normal) * 2;
}
