//
// Created by nicomane on 05/06/22.
//

#include "Camera.h"
#include "Entity.h"


namespace Engine{

    int Camera::currentCamIndex = 0;
    std::vector<Camera *> Camera::cameras;
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
        glm::mat4 Ry_inv = y_rotation(-Angs.y);
        glm::mat4 Rx_inv = x_rotation(-Angs.x);
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

    Camera* Camera::currentCam ;

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
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, nearPlane, farPlane);
        perspectiveMatrix[1][1] *= -1;

        setCamera(this);
    }

    void Camera::switchType(CameraType t){
        type = t;
    }

    glm::mat4 Camera::getPerspectiveMatric() {
        //DEFINE CAMERA PERSPECTIVE
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, nearPlane, farPlane);
        perspectiveMatrix[1][1] *= -1;
        return perspectiveMatrix;
    }

    void Camera::setPerspective(PerspectiveType p){
        //TODO ADD ALL TYPE OF PERSPECTIVE
        perspectiveMatrix = glm::perspective(glm::radians(45.0f), Constants::swapWidth / (float) Constants::swapHeight, 0.1f, 10.0f);
        perspectiveMatrix[1][1] *= -1;
    }

    void Camera::setCamera(Camera* cam){
        currentCam = cam;
    }

    void Camera::addCamera(Camera *cam) {
        cameras.push_back(cam);
        currentCam = cam;
    }

    void Camera::switchCamera(int num) {
        if(num<cameras.size()){
            currentCam = cameras.at(num);
            currentCamIndex=num;
        }
        else{
            std::runtime_error("CAMERA DOSNT EXIST");
        }
    }

    void Camera::setPosition(glm::vec3 p){
        CamPos = p;

    }

    void Camera::onW(float dt) {
        CamPos -= speed * glm::vec3(CamDir[FORWARD_AXIS]) * dt;
        //std::cout<<"POS: ("<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<")\n";
        //viewMatrix = LookInDirMat(CamPos,glm::vec3(0,1,0));
    }
    void Camera::onA(float dt) {
        CamPos += -speed * glm::vec3(CamDir[SIDE_AXIS]) * dt;
        //std::cout<<"POS: ("<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<")\n";
        //viewMatrix = LookInDirMat(CamPos,glm::vec3(0,1,0));
    }
    void Camera::onS(float dt) {
        CamPos += speed * glm::vec3(CamDir[FORWARD_AXIS]) * dt;
        //std::cout<<"POS: ("<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<")\n";
        //viewMatrix = LookInDirMat(CamPos,glm::vec3(0,1,0));//TODO PUT THIS IN UPDATE SCENE,NOT HERE
    }
    void Camera::onD(float dt) {
        CamPos += speed * glm::vec3(CamDir[SIDE_AXIS]) * dt;
       // std::cout<<"POS: ("<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<")\n";
    }

    void Camera::onSpace(float dt){
        CamPos += speed * glm::vec3(CamDir[VERTICAL_AXIS]) * dt;
       // std::cout<<"POS: ("<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<")\n";
    }
    void Camera::onShift(float dt){
        CamPos -= speed * glm::vec3(CamDir[VERTICAL_AXIS]) * dt;
        //std::cout<<"POS: ("<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<")\n";
    }
    void Camera::onE(float dt) {
        CamAng.x += rotation_speed * dt;
        //std::cout<<"Angle: ("<<CamAng.x<<","<<CamAng.y<<","<<CamAng.z<<")\n";
    }

    void Camera::onQ(float dt) {
        CamAng.x -= rotation_speed * dt;
        //std::cout<<"Angle: ("<<CamAng.x<<","<<CamAng.y<<","<<CamAng.z<<")\n";
    }

    void Camera::onDown(float dt) {
        CamAng.x += rotation_speed * dt;
        //std::cout<<"Angle: ("<<CamAng.x<<","<<CamAng.y<<","<<CamAng.z<<")\n";
    }

    void Camera::onUp(float dt) {
        CamAng.x -= rotation_speed * dt;
        //std::cout<<"Angle: ("<<CamAng.x<<","<<CamAng.y<<","<<CamAng.z<<")\n";
    }

    void Camera::onRight(float dt) {
        CamAng.y -= rotation_speed * dt;
        //std::cout<<"Angle: ("<<CamAng.x<<","<<CamAng.y<<","<<CamAng.z<<")\n";
    }

    void Camera::onLeft(float dt) {
        CamAng.y += rotation_speed * dt;
        //std::cout<<"Angle: ("<<CamAng.x<<","<<CamAng.y<<","<<CamAng.z<<")\n";
    }

    void Camera::updateCamDir(){
        CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.y, glm::vec3(0.0f, 1.0f, 0.0f))) *
                           glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.x, glm::vec3(1.0f, 0.0f, 0.0f))) *
                           glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.z, glm::vec3(0.0f, 0.0f, 1.0f)));
    }

    glm::mat4 Camera::getViewMatrix(){
        updateCamDir();
        //std::cout<<"CAM:"<<CamPos.x<<","<<CamPos.y<<","<<CamPos.z<<"\n";
        if(type==LOOK_AT_CAMERA){
            glm::vec3 p=CameraTargetEntity->getPos();
            return glm::lookAt(CamPos,p,glm::vec3(0,1,0));
        }
        //return glm::translate(glm::transpose(glm::mat4(CamDir)), -CamPos);
        return LookInDirMat(CamPos,CamAng);
    }

    void Camera::nextCamera(){

        //Select camera in rotation
        currentCamIndex = (currentCamIndex +1)%cameras.size();
        std::cout << "Current CAM:" <<currentCamIndex <<"\n";
        Camera::switchCamera(currentCamIndex);

        /*

        //auto it = find(cameras.begin(), cameras.end(), currentCam);
        //if(currentCam == nullptr) return; //NO CAMERA SELECTED

         // If element was found
        if (it != cameras.end())
        {

            // calculating the index
            // of K
            int index = it - cameras.begin();
            std::cout << index <<"\n";
            int i=(index+1)%3;
            Camera::switchCamera(i);
           // return index;
        }
        else {
            // If the element is not
            // present in the vector
            std::cout << "-1" << "\n";
        }*/

        //return -1;
    }

    void Camera::setTarget(Entity* target_model){
        CameraTargetEntity=target_model;
    };


}