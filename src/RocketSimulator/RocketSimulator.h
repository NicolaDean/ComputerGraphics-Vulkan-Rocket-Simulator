#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "../engine/App.h"
#include "Models/Rocket.h"
#include "Models/Square.h"
#include "Terrain/Plane.h"
#include "Lights/Skybox.h"
#include "Utils/PerlinNoise.h"
#include "Terrain/Map.h"
#include "../engine/UI/components/UIcomponent.h"


using namespace Engine;

namespace RocketSimulator{
    class RocketSimulator: public Engine::App{

        UIcomponent button;
    public:
        RocketSimulator(int width,int h,std::string win_name):Engine::App(width,h,win_name){
            //Some Code....
        }

        void fff();
        void customInit();
        void customClose(){};
        void rotateSky();
        void changeCameraTarget();
        void switchCamera();
        void nextCamera();
    };
}

