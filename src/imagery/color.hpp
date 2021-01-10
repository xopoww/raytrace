#pragma once

//
// Color management functions
//

#include <cstddef>
#include <cstdint>

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

#include <vector>

// Compute sum(colors[i] * weights[i])
// Result is undefined if sum(weights[i]) != 1 or any of the weights is not
// in range [0, 1]
RGBPixel combine(
    const std::vector<RGBPixel> &colors, const std::vector<float> &weights);

// Combine two colors with proportion a (i.e. a*c1 + (1-a)*c2)
// Result is undefined if a is not in range [0, 1]
RGBPixel combine(const RGBPixel &c1, const RGBPixel &c2, float a);
