#include "color.hpp"


RGBPixel::RGBPixel(): R(0), G(0), B(0) {}

RGBPixel::RGBPixel(const RGBPixel::pixel_t brightness):
R(this->cap(brightness)), G(this->cap(brightness)), B(this->cap(brightness))
{}

RGBPixel::RGBPixel(
    const RGBPixel::pixel_t red,
    const RGBPixel::pixel_t green,
    const RGBPixel::pixel_t blue):
R(this->cap(red)), G(this->cap(green)), B(this->cap(blue))
{}

// static RGBPixel & RGBPixel::from_hex(const char * hex)
// {
// }


RGBPixel combine(
    const std::vector<RGBPixel> &colors, const std::vector<float> &weights)
{
    float rf = 0.f, gf = 0.f, bf = 0.f;
    for (std::size_t i = 0; i < colors.size() && i < weights.size(); i++)
    {
        rf += colors[i].R * weights[i];
        gf += colors[i].G * weights[i];
        bf += colors[i].B * weights[i];
    }
    return RGBPixel{
        (RGBPixel::pixel_t)rf, (RGBPixel::pixel_t)gf, (RGBPixel::pixel_t)bf
    };
}


RGBPixel combine(const RGBPixel &c1, const RGBPixel &c2, float a)
{
    return combine({c1, c2}, {a, 1.f - a});
}