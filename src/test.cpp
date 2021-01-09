#include "imagery/ppm.hpp"
#include "scene.hpp"

#include <iostream>

#define WIDTH 400
#define HEIGHT 300

int main()
{
    Scene scene;

    Camera camera;

    camera.eye = Ray{{}, {0.l, 0.l, -1.l}};
    camera.up = Vector3{0.l, 1.l, 0.l};

    auto img = camera.render(scene);

    std::cout << "Render finished" << std::endl;

    PPMBackend().output(img, "test.ppm");

    std::cout << "Done." << std::endl;
}