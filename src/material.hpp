#pragma once

//
// Optical properties of the bodies in the scene
//

#include "imagery/image.hpp"
#include "linalg/vector.hpp"
#include "linalg/ray.hpp"


struct Material
{
    RGBPixel color;

    Material(const RGBPixel &_color);

    // Returns the scattered ray.
    // Actually, it must also return whether the ray was absorbed and the attenuation,
    // but for simplicity the following system is used:
    //  - if the ray was absorbed, the returned ray's direction will have 0 lehgth
    //  - the attenuation is exactly Material::color (public data field)
    virtual Ray scatter(const Ray &incident, const Ray &normal) const = 0;
};

struct MirrorMaterial : public Material
{
    float noise_coef;

    MirrorMaterial(const RGBPixel &_color, const float _noise);

    Ray scatter(const Ray &incident, const Ray& normal) const override;
};

struct DiffuseMaterial : public Material
{
    float ref_p;

    DiffuseMaterial(const RGBPixel &_color, const float reflect_prob);

    Ray scatter(const Ray &incident, const Ray& normal) const override;
};
