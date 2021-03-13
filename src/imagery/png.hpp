#pragma once

#ifndef LIBPNG_NOT_FOUND

#include "image.hpp"

struct PNGBackend: public ImageBackend
{
    bool output(const RGBImage &image, const char * filename, std::ostream *cerr = &std::cerr) override;
    
    bool output(const RGBImage &image, std::string filename, std::ostream *cerr = &std::cerr) override;
};

#endif
