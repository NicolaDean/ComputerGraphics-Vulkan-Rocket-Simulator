//
// Created by Marco Fasanella on 03/07/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLATFORM_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLATFORM_H
#include "../../engine/core/Objects/Model.h"
#include "../Terrain/Map.h"
#include "../../engine/core/Utils/printHelper.h"
#include "../../engine/core/Core.h"
#include "../../engine/core/Objects/Camera.h"


    namespace Engine {
        class Platform : public Model {
            float speed = 10.0f;
            bool target= false;
        public:
            Platform(BufferManager bufferManager) : Model("./src/Models/platform.obj",
                                                          "./src/Textures/platform.jpg", bufferManager) {
                std::cout << "PLATFORM BUILT\n";
            }


           void setTarget(){
                target=!target;
                if (target){
                    Camera::switchCamera(1); //SET CAM 0 as current Cam

                }
            };


            void update(float dt);

            void close();
            /*************USER INPUT METHODS******************/
            void onI(float dt);

            void onJ(float dt);

            void onK(float dt);

            void onL(float dt);
            glm::vec3* getPos(){
                return &pos;
            }

        };
    };



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
