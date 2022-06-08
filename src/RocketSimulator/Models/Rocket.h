//
// Created by nicomane on 08/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
#include "../../engine/core/Objects/Model.h"

namespace Engine{
    class Rocket:public Model {

    public:
        Rocket(BufferManager bufferManager):Model("./src/Models/rocket.obj",
                                                  "./src/Textures/rocket.jpg",bufferManager){
            std::cout<<"Created a Rocket";
        }
        void update(float dt);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
