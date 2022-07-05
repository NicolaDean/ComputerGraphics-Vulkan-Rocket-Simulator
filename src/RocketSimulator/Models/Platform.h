//
// Created by Marco Fasanella on 03/07/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLATFORM_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLATFORM_H
#include "../../engine/core/Objects/Model.h"
#include "../../engine/core/Utils/printHelper.h"
#include "../../engine/core/Core.h"

    namespace Engine {
        class Platform : public Model {
            float speed = 0.55f;
            bool target= false;
        public:
            Platform(BufferManager bufferManager) : Model("./src/Models/platform.obj",
                                                          "./src/Textures/platform.jpg", bufferManager) {
                std::cout << "PLATFORM BUILT\n";
            }


           void setTarget(){
                target=!target;
            };


            void update(float dt);

            /*************USER INPUT METHODS******************/
            void onI(float dt);

            void onJ(float dt);

            void onK(float dt);

            void onL(float dt);


        };
    };



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
