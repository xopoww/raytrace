#include "imagery/png.hpp"
#include "scene.hpp"

#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080

int main()
{
    Scene scene;

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{60.l, 0.l, -130.l}),
        std::make_shared<MirrorMaterial>(RGBPixel{0xA0, 0x80, 0x20}, 0.3f)
    });

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{-60.l, 0.l, -170.l}),
        std::make_shared<DiffuseMaterial>(RGBPixel{0x10, 0x40, 0x60}, 0.5f)
    });

    scene.add_body({
        std::make_shared<Sphere>(1000.l, Vector3{0.l, -1050.l, -150.l}),
        std::make_shared<DiffuseMaterial>(RGBPixel{0x50, 0x50, 0x50}, 0.5f)
    });


    Camera camera{
        {{}, {0.l, 0.l, -1.l}},
        {0.l, 1.l, 0.l},
        {HEIGHT, WIDTH},
        1.6l,
        10
    };

    auto img = camera.render(scene);

    std::cout << "Render finished" << std::endl;

    PNGBackend().output(img, "highres_demo_01.png");

    std::cout << "Done." << std::endl;
}
