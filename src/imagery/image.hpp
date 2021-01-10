#pragma once

#include <string>

#include "color.hpp"

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
