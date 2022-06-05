//
// Created by nicomane on 05/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H

#include "../../commonLibs.h"

namespace Engine{
    enum CameraType { LOOK_AT_CAMERA, LOOK_IN_DIRECTION};
    enum Perspective {ORTOGONALE};

    class Camera {
    public:
        static Camera* currentCam;

        CameraType type;
        Perspective perspective;
        glm::mat4 viewMatrix;
        glm::mat4 perspectiveMatrix;

        Camera();

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
