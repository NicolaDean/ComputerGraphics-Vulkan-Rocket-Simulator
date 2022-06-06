//
// Created by nicomane on 05/06/22.
//

#include "Camera.h"


namespace Engine{


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

        glm::mat4 out = Rz_inv * Rx_inv * Ry_inv * T_inv;
        return out;
    }

/**
  * Create a look at matrix
  * @param Pos Position of the camera (c)
  * @param aim Position of the target (a)
  * @param Roll roll (rho)
  * @return
  */
    glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {

        glm::vec3 u = glm::vec3(0,1,0);//Vertical orientation

        //ROLL is a z rotation before lookat
        return z_rotation(Roll) * glm::lookAt(Pos,aim,u);
    }

    Camera* Camera::currentCam = new Camera();

    //TODO ADD METHODS TO MOVE CAMERA AND TO CHANGE SETTINGS (focal lenght etc..)
    Camera::Camera():Entity() {
        switchType(LOOK_IN_DIRECTION);
        setPerspective(ORTOGONALE);
        setCamera(this);
    }

    Camera::Camera(CameraType t,PerspectiveType p):Entity()  {
        //DEFINE CAMERA TYPE
        switchType(type);

        //DEFINE CAMERA PERSPECTIVE
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, 0.1f, 10.0f);
        perspectiveMatrix[1][1] *= -1;

        setCamera(this);
    }


    void Camera::switchType(CameraType t){
        type = t;
        if(type == LOOK_AT_CAMERA){
            LookAtMat(glm::vec3(5.0f, 5.0f, 5.0f),glm::vec3(0.0f, 0.0f, 0.0f),0);
            //viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if(type == LOOK_IN_DIRECTION){
            //TODO FIND HOW DO
            viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

    void Camera::setPerspective(PerspectiveType p){
        //TODO ADD ALL TYPE OF PERSPECTIVE
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, 0.1f, 10.0f);
        perspectiveMatrix[1][1] *= -1;
    }

    void Camera::setCamera(Camera* cam){
        currentCam = cam;
    }
}