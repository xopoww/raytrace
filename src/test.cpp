#include "imagery/ppm.hpp"
#include "scene.hpp"

#include <iostream>

#define WIDTH 200
#define HEIGHT 150

int main()
{
    Scene scene;

    scene.add_body({
        std::make_shared<Sphere>(50.l, Vector3{0.l, 0.l, -200.l}),
        {{0xFF, 0, 0}}
    });

    Camera camera{
        {{}, {0.l, 0.l, -1.l}},
        {0.l, 1.l, 0.l},
        {HEIGHT, WIDTH},
        1.6l,
        0
    };

    auto img1 = camera.render(scene);
    
    camera.anti_aliasing = 4;

    auto img2 = camera.render(scene);

    camera.anti_aliasing = 10;

    auto img3 = camera.render(scene);

    std::cout << "Render finished" << std::endl;

    PPMBackend().output(img1, "test1.ppm");
    PPMBackend().output(img2, "test2.ppm");
    PPMBackend().output(img3, "test3.ppm");

    std::cout << "Done." << std::endl;
}
