//
// Created by nicomane on 05/06/22.
//

#include "Camera.h"


namespace Engine{

    Camera* Camera::currentCam = new Camera();

    Camera::Camera() {
        viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //TODO SET THE SWAPCHAIN EXTENT WIDTH AND HEIGHT IN THE GLOBAL VAIRABLES SINGLETON
        //perspectiveMatrix = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
        //perspectiveMatrix[1][1] *= -1;
    }
}