#pragma once

#include "image.hpp"

struct PNGBackend: public ImageBackend
{
    bool output(const RGBImage &image, const char * filename, std::ostream *cerr = &std::cerr) override;
    
    bool output(const RGBImage &image, std::string filename, std::ostream *cerr = &std::cerr) override;
};
