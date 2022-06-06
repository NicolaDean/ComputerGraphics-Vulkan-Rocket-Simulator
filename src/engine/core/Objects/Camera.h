//
// Created by nicomane on 05/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H

#include "../../commonLibs.h"
#include "../Utils/Constants.h"
#include "Entity.h"
#include "Camera.h"

namespace Engine{

    glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs);
    glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll);

    enum CameraType { LOOK_AT_CAMERA, LOOK_IN_DIRECTION};
    enum PerspectiveType {ORTOGONALE};

    class Camera:public Entity {
    public:
        static Camera* currentCam;

        CameraType type;
        PerspectiveType perspective;
        glm::mat4 viewMatrix;
        glm::mat4 perspectiveMatrix;

        //Contain a pointer to a target to look
        Entity* CameraTarget;

        /*************CAMERA CONSTRUCTORS********************/
        Camera();
        Camera(CameraType t,PerspectiveType p);
        static void setCamera(Camera* cam);

        /***************CAMERA MOVEMENT******************/
        //Maybe put those in entity equal for model and camera
        /***************CAMERA SETTINGS******************/
        void switchType(CameraType t);
        void setPerspective(PerspectiveType p);

        //void setTarget(Entity* target_model);
        //void setTarget(glm::vec3 target_position);
        //void setUp(glm::vec3 up);
        // -> eg if we want a camera that track the rocket from bottom following and alligning to it(like in space x lives)
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
