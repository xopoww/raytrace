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
        1.6l
    };

    auto img = camera.render(scene);

    std::cout << "Render finished" << std::endl;

    PPMBackend().output(img, "test.ppm");

    std::cout << "Done." << std::endl;
}
