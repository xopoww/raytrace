#include "png.hpp"

#include <libpng/png.h>
#include <cstdio>

#define RT_PNG_ERROR(msg)                   \
if (cerr) { *cerr << msg << std::endl; }    \
return false

bool PNGBackend::output(const RGBImage &image, const char * filename, std::ostream *cerr)
{
    auto shape = image.shape();
    std::size_t height = shape.first;
    std::size_t width = shape.second;


    // setup libpng output
    FILE *fp = std::fopen(filename, "wb");
    if (!fp)
    {
        RT_PNG_ERROR("failed to open file \"" << filename << "\"");
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr)
    {
        RT_PNG_ERROR("failed to create png write struct");
    }
    
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
        RT_PNG_ERROR("failed to create png info struct");
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        RT_PNG_ERROR("failed to init io");
    }

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        RT_PNG_ERROR("failed to write png settings");
    }

    png_set_IHDR(
        png_ptr, info_ptr,
        width, height,
        RGBPixel::bit_depth, PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(png_ptr, info_ptr);


    // convert an image to libpng repr (might be subject for optimization)

    png_bytep *rows = new png_bytep[height];
    
    for (std::size_t i = 0; i < height; i++)
    {
        rows[i] = new png_byte[width * 3];
        for (std::size_t j = 0; j < width; j++)
        {
            rows[i][j * 3 + 0] = (png_byte)image(i, j).R;
            rows[i][j * 3 + 1] = (png_byte)image(i, j).G;
            rows[i][j * 3 + 2] = (png_byte)image(i, j).B;
        }
    }

    auto cleanup = [&](){
        for (std::size_t i = 0; i < height; i++)
        {
            delete[] rows[i];
        }
        delete[] rows;
    };


    // write the image

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        cleanup();
        RT_PNG_ERROR("failed to write png image");
    }

    png_write_image(png_ptr, rows);

    png_write_end(png_ptr, NULL);


    // finalize

    png_destroy_write_struct(&png_ptr, &info_ptr);
    cleanup();
    return true;
}

bool PNGBackend::output(const RGBImage &image, std::string filename, std::ostream *cerr)
{
    return this->output(image, filename.c_str(), cerr);
}