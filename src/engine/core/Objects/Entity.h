//
// Created by nicomane on 06/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H

#include "../../commonLibs.h"
namespace Engine{
    //IDENTITY MATRIX
    const glm::mat4 I = glm::mat4(1);
    //AXIS DEFINITION
    const glm::vec3 x_axis = glm::vec3(1,0,0);
    const glm::vec3 y_axis = glm::vec3(0,1,0);
    const glm::vec3 z_axis = glm::vec3(0,0,1);

    glm::mat4 x_rotation(float angle);
    glm::mat4 y_rotation(float angle);
    glm::mat4 z_rotation(float angle);

    class Entity{
        //MESH WORLD INFO
        glm::vec3 pos = glm::vec3(1,1,1);
        glm::vec3 orientation = glm::vec3(0,0,1);
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        bool WASD_movement;
        bool updateMovement;

    public:
        Entity(){

        }
        /********************MOVEMENT********************************/

        void move(){
            modelMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
        }

        glm::mat4 getModelMatrix(){
            return modelMatrix;
        }

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H
