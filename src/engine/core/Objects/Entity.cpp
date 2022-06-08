//
// Created by nicomane on 06/06/22.
//

#include "Entity.h"


namespace Engine{
    /**
 * rotate around x
 * @param angle rotation angle
 * @return matrix to rotate around x
 */
    glm::mat4 x_rotation(float angle)
    {
        return glm::rotate(I,angle,x_axis);
    }
/**
 * rotate around y
 * @param angle rotation angle
 * @return matrix to rotate around y
 */
    glm::mat4 y_rotation(float angle)
    {
        return glm::rotate(I,angle,y_axis);
    }
/**
 * rotate around z
 * @param angle rotation angle
 * @return matrix to rotate around z
 */
    glm::mat4 z_rotation(float angle)
    {
        return glm::rotate(I,angle,z_axis);
    }
    /***************KEY COMMANDS********/
    void Entity::onW(float dt) {}
    void Entity::onA(float dt) {}
    void Entity::onS(float dt) {}
    void Entity::onD(float dt) {}
    void Entity::onE(float dt) {}

    void Entity::customKeys(float dt) {}

}