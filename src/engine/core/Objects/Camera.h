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
        static int currentCamIndex;
        static Camera* currentCam;

        /***********CAM SETTINGS VARIABLES*************/
        CameraType type;
        PerspectiveType perspective;
        float nearPlane = 0.1f;
        //How far you can see
        float farPlane  = 200.0f;
        /***********CAMERA MOVEMENT VARIABLES***********/
        glm::vec3 CamPos = glm::vec3(1,1.5,2);
        glm::vec3 CamAng = glm::vec3(0,0,0);
        glm::mat3 CamDir = I;
        float speed =0.55f;
        float rotation_speed = glm::radians(60.0f);
        /**********MATRIX*****************/
        glm::mat4 viewMatrix;
        glm::mat4 perspectiveMatrix;

        //Contain a pointer to a target to look
        Entity* CameraTarget;

        glm::mat4 getCamPosTranslate(){
            return glm::transpose(glm::mat4(CamDir));
        }
        /*************CAMERA CONSTRUCTORS********************/
        Camera();
        Camera(CameraType t,PerspectiveType p);
        static void setCamera(Camera* cam);

        /*************SWITCH CAMERA**********************/
        static std::vector<Camera*> cameras; //List of existing cameras
        static void addCamera(Camera* cam); //Add a camera to list of cameras
        static void switchCamera(int num); //Switch to a specific camera
        static void nextCamera();

        /***************CAMERA MOVEMENT******************/
        //Maybe put those in entity equal for model and camera
        void updateCamDir();
        void setPosition(glm::vec3 p);
        void setAngle(glm::vec3 a){CamAng = a;}
        /***************CAMERA SETTINGS******************/
        void switchType(CameraType t);
        void setPerspective(PerspectiveType p);
        void setNearPlane(float n){nearPlane = n;};
        void setFarPlane(float f){farPlane = f;};

        /*************USER INPUT METHODS******************/
        void onW(float dt);
        void onA(float dt);
        void onS(float dt);
        void onD(float dt);
        void onQ(float dt);
        void onE(float dt);
        void onSpace(float dt);
        void onShift(float dt);
        void onUp(float dt);
        void onDown(float dt);
        void update(float dt){};
        void onLeft(float dt);
        void onRight(float dt);

        glm::mat4 getViewMatrix();
        glm::mat4 getPerspectiveMatric();
        //void setTarget(Mesh* target_model);
        //void setTarget(glm::vec3 target_position);
        //void setUp(glm::vec3 up);
        // -> eg if we want a camera that track the rocket from bottom following and alligning to it(like in space x lives)
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_CAMERA_H
