#pragma once

//
// Optical properties of the bodies in the scene
//

#include "imagery/image.hpp"
#include "linalg/vector.hpp"


struct Material
{
    virtual Vector3 reflect(
        const Vector3 &direction, const Vector3 &normal) const = 0;

    RGBPixel color;

    Material(const RGBPixel &_color);
};

struct MirrorMaterial : public Material
{

    MirrorMaterial(const RGBPixel &_color);

    Vector3 reflect(
        const Vector3 &direction, const Vector3 &normal) const override;
};
