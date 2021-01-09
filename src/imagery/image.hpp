#pragma once

#include <cstddef>
#include <cstdint>
#include <string>


struct RGBPixel
{
    using pixel_t = uint16_t;
    static const pixel_t max_brightness = 0xFF;

    pixel_t R;
    pixel_t G;
    pixel_t B;

    RGBPixel();

    RGBPixel(const pixel_t brightness);

    RGBPixel(const pixel_t red, const pixel_t green, const pixel_t blue);

    static RGBPixel & from_hex(const char * hex);

private:

    inline static pixel_t cap(const pixel_t val)
    {
        return val > max_brightness ? max_brightness : val;
    }

};

#include "../linalg/matrix.hpp"

using RGBImage = BasicMatrix<RGBPixel>;


#include <functional>

using color_rule_t = std::function<RGBPixel(const RGBPixel &)>;

color_rule_t static_color(const RGBPixel &col);


struct ImageBackend
{
    virtual void output(const RGBImage &image, const char * filename) = 0;
    
    virtual void output(const RGBImage &image, std::string filename) = 0;
};
