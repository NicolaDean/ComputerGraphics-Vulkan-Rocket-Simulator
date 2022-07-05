
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "./RocketSimulator/RocketSimulator.h"

const uint32_t WIDTH = 650;
const uint32_t HEIGHT = 480;

int main() {
    //App::App app = App::App();
    RocketSimulator::RocketSimulator rocketSimulator = RocketSimulator::RocketSimulator(WIDTH,HEIGHT,"Rocket Simulator");
    try {
        rocketSimulator.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    return 0;
}