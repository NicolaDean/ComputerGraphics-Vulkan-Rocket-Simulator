//
// Created by nicomane on 05/06/22.
//

#include "Camera.h"


namespace Engine{

    Camera* Camera::currentCam = new Camera();

    //TODO ADD METHODS TO MOVE CAMERA AND TO CHANGE SETTINGS (focal lenght etc..)
    Camera::Camera():Entity() {
        viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, 0.1f, 10.0f);
        perspectiveMatrix[1][1] *= -1;
        Camera::currentCam = this;
    }

    Camera::Camera(bool a):Entity()  {
        viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, 0.1f, 10.0f);
        perspectiveMatrix[1][1] *= -1;
        Camera::currentCam = this;
    }

    void Camera::setCamera(Camera* cam){
        currentCam = cam;
    }
}