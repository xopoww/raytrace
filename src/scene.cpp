#include "scene.hpp"

#include "linalg/random.hpp"

#include <cmath>

const coord_t pixel_size = 1.l;


Camera::Camera():
    eye({0.l, 0.l, 0.l}, {0.l, 0.l, -1.0}),
    up(0.l, 1.l, 0.l),
    width(400), height(300), FOV(1.6l)
{}

Camera::Camera(
    const Ray &_eye, const Vector3 &_up,
    std::pair<std::size_t, std::size_t> _shape, const long double _FOV,
    const std::size_t _anti_aliasing
):
    eye(_eye.origin, _eye.direction.norm()),
    up(_up.norm()), width(_shape.second), height(_shape.first), FOV(_FOV),
    anti_aliasing(_anti_aliasing)
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

void Scene::add_body(const Body &body)
{
    this->bodies.emplace_back(body);
}

RGBImage Camera::render(const Scene &scene) const
{
    RGBImage img(this->width, this->height, RGBPixel());

    Vector3 right = this->eye.direction.cross(this->up);

    for (std::size_t x = 0; x < this->width; x++)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            coord_t base_off_x = x - (coord_t)this->width / 2;
            coord_t base_off_y = y - (coord_t)this->height / 2;

            std::vector<RGBPixel> samples;
            samples.reserve(this->anti_aliasing);

            auto add_sample =
                [&samples, base_off_x, base_off_y, right, this, scene]
                (const coord_t sub_off_x, const coord_t sub_off_y)
            {
                coord_t off_x = base_off_x + sub_off_x * pixel_size;
                coord_t off_y = base_off_y + sub_off_y * pixel_size;

                Vector3 direction = this->vec_to_screen()
                + right * off_x - this->up * off_y;

                Ray ray(this->eye.origin, direction);

                samples.push_back(this->trace(ray, scene));
            };

            std::vector<float> weights;

            if (this->anti_aliasing == 0)
            {
                add_sample(0.5l, 0.5l);

                weights.push_back(1.f);
            }
            else
            {
                for (std::size_t i = 0; i < this->anti_aliasing; i++)
                {
                    add_sample(random_frac(), random_frac());
                }

                weights = std::vector<float>(
                    this->anti_aliasing, 1.f / this->anti_aliasing);
            }

            img(y, x) = combine(samples, weights);
        }
    }

    return img;
}

const coord_t max_render_distance = 1000.l;

RGBPixel Camera::trace(const Ray &ray, const Scene &scene) const
{
    std::vector<Ray> intersects;

    for (std::size_t i = 0; i < scene.bodies.size(); i++)
    {
        if (scene.bodies[i].obj->is_in(this->eye.origin))
        {
            intersects.emplace_back(inf_vector, Vector3{});
        }

        intersects.push_back(scene.bodies[i].obj->intersect(ray).first);
    }

    coord_t min_dist = infinity;
    int body_index = -1;

    for (std::size_t i = 0; i < scene.bodies.size(); i++)
    {
        if (std::isnan(intersects[i].origin.x) || std::isinf(intersects[i].origin.x))
        {
            continue;
        }
        coord_t dist = (intersects[i].origin - this->eye.origin).length();
        if (dist < min_dist)
        {
            min_dist = dist;
            body_index = i;
        }
    }

    if (body_index != -1)
    {
        return scene.bodies[body_index].material.color;
    }


    long double cos_phi =
        ray.direction.norm().dot((scene.light - this->eye.origin).norm());

    long double lum = std::pow((cos_phi + 1.l) / 2.l, 4);

    RGBPixel::pixel_t brightness = RGBPixel::max_brightness * lum;

    RGBPixel computed_color{brightness};

    return computed_color;
}
  