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

    /**
     * Create a look in direction matrix
     * @param Pos Position of the camera
     * @param Angs Angs.x -> direction (alpha)
     *             Angs.y -> elevation (beta)
     *             Angs.z -> roll (rho)
     * @return first person matrix
     */
    glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {

        //INVERSE TRANSFORMATION
        glm::mat4 T_inv = glm::translate(I,-Pos);
        glm::mat4 Ry_inv = y_rotation(-Angs.x);
        glm::mat4 Rx_inv = x_rotation(-Angs.y);
        glm::mat4 Rz_inv = z_rotation(-Angs.z);

        //glm::mat4 out = T_inv * Ry_inv * Rx_inv * Rz_inv;
        glm::mat4 out = Rz_inv * Rx_inv * Ry_inv * T_inv;
        return out;
    }

}