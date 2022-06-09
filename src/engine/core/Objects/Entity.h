//
// Created by nicomane on 06/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H

#include "../../commonLibs.h"

//AXIS
#define FORWARD_AXIS 2
#define SIDE_AXIS 0
#define VERTICAL_AXIS 1

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
    protected:
        //MESH WORLD INFO
        glm::vec3 pos = glm::vec3(1,1,1);
        glm::vec3 orientation = glm::vec3(0,0,1);
        glm::mat3 directionMat = I;
        float scalingFactor = 1;
        //Vulkan World Matrix
        glm::mat4 modelMatrix = glm::mat4(1.0f);


    public:
        Entity(){

        }
        /********************MOVEMENT********************************/

        float scaling = 1.0f;

        void move(){
            scaling = scaling/2.0f;
            modelMatrix =glm::translate(glm::mat4(1.0f),pos) * glm::scale(glm::mat4(1.0f),glm::vec3(0.03));
        }

        glm::mat4 getModelMatrix(){
            //TODO PUT translate * rotate * scale (in the right order, as for camera)
            modelMatrix =glm::translate(glm::mat4(1.0f),pos) * glm::scale(glm::mat4(1.0f),glm::vec3(scalingFactor));
            return modelMatrix;
        }

        /*************MODEL SCAL POS ROT***************/
        void setScale(float s){
            scalingFactor = s;
        }

        void setPos(glm::vec3 p){
            pos = p;
        }

        void setAngles(glm::vec3 a){
            orientation = a;
        }
        /*************MOVABLE METHODS******************/
        void onW(float dt);
        void onA(float dt);
        void onS(float dt);
        void onD(float dt);
        void onQ(float dt);
        void onE(float dt);
        void customKeys(float dt); //Allow user to add functionality on other keys not covered

        virtual void update(float dt) = 0;
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_ENTITY_H
