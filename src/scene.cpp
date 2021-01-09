#include "scene.hpp"

#include <cmath>

const coord_t pixel_size = 1.l;


Camera::Camera():
    eye({0.l, 0.l, 0.l}, {0.l, 0.l, -1.0}),
    up(0.l, 1.l, 0.l),
    width(400), height(300), FOV(1.6l)
{}

Camera::Camera(
    const Ray &_eye, const Vector3 &_up,
    std::pair<std::size_t, std::size_t> _shape, const long double _FOV
):
    eye(_eye.origin, _eye.direction.norm()),
    up(_up.norm()), width(_shape.second), height(_shape.first), FOV(_FOV)
{}

Vector3 Camera::vec_to_screen() const
{
    coord_t dist_to_screen = pixel_size * this->width / 2
        / std::tan(this->FOV / 2);
    return this->eye.direction.norm() * dist_to_screen;
}


Scene::Scene(): light(0.l, 100.l, 0.l) {}

Scene::Scene(const Vector3 &_light): light(_light)
{
}

RGBImage Camera::render(const Scene &scene) const
{
    RGBImage img(this->width, this->height, RGBPixel());

    Vector3 right = this->eye.direction.cross(this->up);

    for (std::size_t x = 0; x < this->width; x++)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            coord_t off_x = x - ((coord_t)this->width - pixel_size) / 2;
            coord_t off_y = y - ((coord_t)this->height - pixel_size) / 2;

            Vector3 direction = this->vec_to_screen()
                + right * off_x - this->up * off_y;

            Ray ray(this->eye.origin, direction);

            img(y, x) = this->trace(ray, scene);
        }
    }

    return img;
}

const coord_t max_render_distance = 1000.l;

RGBPixel Camera::trace(const Ray &ray, const Scene &scene) const
{
    long double cos_phi =
        ray.direction.norm().dot((scene.light - this->eye.origin).norm());

    long double lum = std::pow((cos_phi + 1.l) / 2.l, 4);

    RGBPixel::pixel_t brightness = RGBPixel::max_brightness * lum;

    RGBPixel computed_color{brightness};

    return computed_color;
}
  