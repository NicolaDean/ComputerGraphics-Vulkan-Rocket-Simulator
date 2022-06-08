//
// Created by nicomane on 08/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
#include "../../engine/core/Objects/Model.h"

namespace Engine{
    class Rocket:public Model {
//Set renderer? renderer = renderer;
        //Bools for explosion and deletion
        bool explosion = false;
        bool deleted=false;
        bool launched = false;

        glm::vec3 pos = glm::vec3(0);

        // Rotation around its axis
        float roll= 0.0f;
        float rspe= 0.0f;

        // Vec2 direction on XZ plane for decomposing velocity and acceleration
        glm::vec2 hdir     = glm::vec2(0, 0);

        // Propulsion timeout
        float timeout  = 0;

        // Time to live before reaching target
        float ttl= 0;

        // Acceleration and velocity XZ and Y components
        glm::vec2 verticalAcceleration    = glm::vec2(0, 0);
        glm::vec2 verticalVelocity    = glm::vec2(0, 0);
        float pitch= - M_PI / 2;



        // Horizontal and vertical scale
        float hscale  = 1;
        float vscale =1;
    public:
        Rocket(BufferManager bufferManager):Model("./src/Models/rocket.obj",
                                                  "./src/Textures/rocket.jpg",bufferManager){
            std::cout<<"ROCKET COSTRUITO\n";
        }
        void launch(){
            std::cout<<"LAUNCHED\n";
        }
        virtual void update(float dt);
        void trajectory(glm::vec3 target, float highMax, float vAcc);
        void updateAcceleration(float dt);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
