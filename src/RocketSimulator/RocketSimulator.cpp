#include "RocketSimulator.h"

using namespace Engine;

namespace RocketSimulator{

    void RocketSimulator::customInit() {
        Camera::setCamera(new Camera(LOOK_IN_DIRECTION,ORTOGONALE));
        Camera::currentCam->setPosition({1,1,2});
        Camera::currentCam->setAngle({0.1,0,0});

        //MODEL 1:
        Model* m1 = new Model("./src/Models/cube.obj",
                              "./src/Textures/cube.jpg",bufferManager);
        m1->init();
        m1->initDescriptor(&descManager);
        Mesh::meshes->push_back(m1);

        //MODEL 2:
        Rocket* m2 = new Rocket(bufferManager);
        m2->init();
        m2->initDescriptor(&descManager);

        Mesh::meshes->push_back(m2);
        this->subscribeMovable(m2);
        m2->launch();
    }
}