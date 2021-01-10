#pragma once

#include "linalg/vector.hpp"
#include "linalg/ray.hpp"
#include "imagery/image.hpp"
#include "body.hpp"

#include <vector>

class Scene
{
    Vector3 light;

    std::vector<Body> bodies;

public:

    Scene();

    Scene(const Vector3 &_light);

    void add_body(const Body &body);

    friend struct Camera;
};


struct Camera
{
    Ray eye;
    Vector3 up;

    std::size_t width;
    std::size_t height;

    long double FOV;

    Camera();

    Camera(
        const Ray &_eye, const Vector3 &_up,
        std::pair<std::size_t, std::size_t> _shape, const long double _FOV);

    RGBImage render(const Scene &scene) const;

private:

    Vector3 vec_to_screen() const;

    RGBPixel trace(const Ray &ray, const Scene &scene) const;
};
