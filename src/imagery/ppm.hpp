#pragma once

#include "image.hpp"

struct PPMBackend: public ImageBackend
{
    void output(const RGBImage &image, const char * filename) override;
    
    void output(const RGBImage &image, std::string filename) override;
};
