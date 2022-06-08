#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "../engine/App.h"
#include "Models/Rocket.h"

namespace RocketSimulator{
    class RocketSimulator: public Engine::App{

    public:
        RocketSimulator(int width,int h,std::string win_name):Engine::App(width,h,win_name){
            //Some Code....
        }

        void customInit();
    };
}

