//
// Created by nicomane on 06/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H

#include "../../commonLibs.h"
namespace Engine{
    class Entity{
        //MESH WORLD INFO
        glm::vec3 pos = glm::vec3(1,1,1);
        glm::vec3 orientation = glm::vec3(0,0,1);
        glm::mat4 modelMatrix = glm::mat4(1.0f);

    public:
        Entity(){

        }
        /********************MOVEMENT********************************/

        void move(){
            modelMatrix = glm::translate(glm::mat4(1.0f),pos);
        }

        glm::mat4 getModelMatrix(){
            return modelMatrix;
        }

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H
