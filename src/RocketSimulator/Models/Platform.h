//
// Created by Marco Fasanella on 03/07/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLATFORM_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLATFORM_H
#include "../../engine/core/Objects/Model.h"
#include "../../engine/core/Utils/printHelper.h"

    namespace Engine{
        class Platform:public Model {

        public:
            Platform(BufferManager bufferManager):Model("./src/Models/platform.obj",
            "./src/Textures/platform.jpg",bufferManager){
                std::cout<<"PLATFORM BUILT\n";
            }
        };
    }



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
