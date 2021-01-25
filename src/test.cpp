#include "imagery/ppm.hpp"
#include "scene.hpp"

#include <iostream>

#define WIDTH 500
#define HEIGHT 300

int main()
{
    Scene scene;

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{60.l, 0.l, -150.l}),
        std::make_shared<MirrorMaterial>(RGBPixel{0xFF, 0, 0}, 0.4f)
    });

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{-60.l, 0.l, -150.l}),
        std::make_shared<MirrorMaterial>(RGBPixel{0xFF, 0xFF, 0xFF}, 0.15f)
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

    PPMBackend().output(img, "test.ppm");

    std::cout << "Done." << std::endl;
}
