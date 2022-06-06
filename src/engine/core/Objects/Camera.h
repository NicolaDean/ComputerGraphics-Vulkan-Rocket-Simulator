//
// Created by nicomane on 05/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H

#include "../../commonLibs.h"
#include "../Utils/Constants.h"
#include "Entity.h"
namespace Engine{
    enum CameraType { LOOK_AT_CAMERA, LOOK_IN_DIRECTION};
    enum Perspective {ORTOGONALE};

    class Camera:public Entity {
    public:
        static Camera* currentCam;

        CameraType type;
        Perspective perspective;
        glm::mat4 viewMatrix;
        glm::mat4 perspectiveMatrix;

        Camera();
        Camera(bool a);

        static void setCamera(Camera* cam);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
