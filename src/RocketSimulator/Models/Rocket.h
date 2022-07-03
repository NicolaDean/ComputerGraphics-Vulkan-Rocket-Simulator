//
// Created by nicomane on 08/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
#include "../../engine/core/Objects/Model.h"
#include "../../engine/core/Utils/printHelper.h"
namespace Engine{
    class Rocket:public Model {
        //Bools for explosion and deletion
        bool explosion = false;
        bool deleted=false;
        bool launched = false;
        bool landing=false;

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

        float maxHeight=0.0f;
        float offsetHeight=0.0f;
        float startHeight =0.0f;
        float landingFactorx=0.0f;
        float landingFactory=0.0f;

        // Horizontal and vertical scale
        float hscale  = 1;
        float vscale =1;
    public:
        Rocket(BufferManager bufferManager):Model("./src/Models/rocket.obj",
                                                  "./src/Textures/rocket.jpg",bufferManager){
            std::cout<<"ROCKET COSTRUITO\n";
        }
        void launch(){
            std::cout<<"LAUNCHED ROCKETTTTTTT\n";
            launched=true;
        }
        virtual void update(float dt);
        void close();
        void checkPosition();
        void trajectory(glm::vec3 target, float heightMax, float vAcc);
        void updateAcceleration(float dt);
        glm::vec3 getPosition(){
            return this->pos;
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ROCKET_H
