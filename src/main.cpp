
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "./myapp/MyApp.h"

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

int main() {
    //App::App app = App::App();
    MyApp::MyApp assignment13 = MyApp::MyApp(WIDTH,HEIGHT,"Assignment 13");
    try {
        assignment13.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    return 0;
}