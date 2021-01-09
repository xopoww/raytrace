#include "ppm.hpp"

#include <fstream>

void PPMBackend::output(const RGBImage &image, const char * filename)
{
    std::ofstream fout;
    fout.open(filename);

    auto shape = image.shape();
    fout << "P3" << std::endl
        << shape.second << " " << shape.first << std::endl
        << "255" << std::endl;
    
    for (std::size_t i = 0; i < shape.first; i++)
    {
        for (std::size_t j = 0; j < shape.second; j++)
        {
            fout << image(i, j).R << " "
                << image(i, j).G << " "
                << image(i, j).B << std::endl;
        }
    }

    fout.close();
}

void PPMBackend::output(const RGBImage &image, std::string filename)
{
    return this->output(image, filename.c_str());
}