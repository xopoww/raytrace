#include "imagery/png.hpp"
#include "scene.hpp"

#include <cmath>
#include <iostream>

#define WIDTH 400
#define HEIGHT 300

int main()
{
    Scene scene{{0.l, 200.l, 150.l}};

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{60.l, 0.l, -130.l}),
        std::make_shared<MirrorMaterial>(RGBPixel{0x80, 0xA0, 0x20}, 0.3f)
    });

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{-60.l, 0.l, -170.l}),
        std::make_shared<MirrorMaterial>(RGBPixel{0x60, 0x40, 0x10}, 0.05f)
    });

    scene.add_body({
        std::make_shared<Sphere>(10.l, Vector3{15.l, -40.l, -90.l}),
        std::make_shared<DiffuseMaterial>(RGBPixel{0x84, 0x44, 0x04}, 0.5f)
    });

    scene.add_body({
        std::make_shared<Sphere>(1000.l, Vector3{0.l, -1050.l, -150.l}),
        std::make_shared<DiffuseMaterial>(RGBPixel{0x50, 0x50, 0x50}, 0.5f)
    });


    Camera camera{
        {{0.l, 0.l, 40.l}, {0.055l, 0.l, -1.l}},
        {0.l, 1.l, 0.l},
        {HEIGHT, WIDTH},
        1.2l,
        4
    };

    Progress::callback_t callback = [](const std::size_t curr, const std::size_t total)
    {
        std::size_t percent = 100 * curr / total;
        std::cout << "\t" << percent << "% done" << (curr == total ? "\n" : "\r");
        std::cout.flush(); 
    };

    std::cout << "Starting the rendering..." << std::endl;

    auto img = camera.render(scene, callback);

    std::cout << "Render finished" << std::endl;

    PNGBackend().output(img, "test.png");

    std::cout << "Done." << std::endl;
}
