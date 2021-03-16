#pragma once

#include <string>

#include "color.hpp"

#include "linalg/matrix.hpp"

using RGBImage = BasicMatrix<RGBPixel>;

#include <iostream>
#include <functional>

using color_rule_t = std::function<RGBPixel(const RGBPixel &)>;

color_rule_t static_color(const RGBPixel &col);


struct ImageBackend
{
    // Output an image to the file (the format is defined bt the exact subclass of ImageBackend).
    // If an error is encountered, false is returned and the error description
    // is printed to the stream pointed to by cerr (if cerr is nullptr, nothing is printed).
    virtual bool output(const RGBImage &image, const char * filename, std::ostream *cerr = &std::cerr) = 0;
    
    virtual bool output(const RGBImage &image, std::string filename, std::ostream *cerr = &std::cerr) = 0;
};
