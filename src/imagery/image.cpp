#include "image.hpp"

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
