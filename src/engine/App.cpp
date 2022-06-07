//
// Created by nicomane on 02/06/22.
//

#include "App.h"

namespace Engine{

    void App::updateCamera(float dt){
        if(glfwGetKey(window, GLFW_KEY_A)) {
            Camera::currentCam->onA(dt);
        }
        if(glfwGetKey(window, GLFW_KEY_S)) {
            Camera::currentCam->onS(dt);
        }
        if(glfwGetKey(window, GLFW_KEY_W)) {
            Camera::currentCam->onW(dt);
        }
        if(glfwGetKey(window, GLFW_KEY_D)) {
            Camera::currentCam->onD(dt);
        }
    }
    void App::updateScene(uint32_t currentFrame) {
        //TODO CREATE A CLASS TO MANAGE TIME
        static float lastTime = 0.0f;
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        float deltaT = time - lastTime;
        lastTime = time;

        /********UPDATE CAMERA*************/
        updateCamera(deltaT);

        /********UPDATE MOVABLE OBJECT*************/
        //TODO ACCESS "MOVABLE OBJECTS IN A SEPARATE LOOP"
        //updateEntitys(deltaT);
        /********CALCULATE STATIC MESHES POSITION*************/
        updateMeshesPos(currentFrame);
    }
    //TODO ADD A GRAPHIC PIPELINE WITH ONLY VERTEX/INDEX WITH NO TEXTURE (FOR THE TERRAIN GENERATOR)
    void App::updateMeshesPos(int currentFrame) {
        //SIMPLY UPDATE UNIFOMR BUFFERS OF ALL MESHES
        for (auto mesh : *Mesh::meshes)
        {
            mesh->move();
            mesh->updateUniformBuffer(currentFrame);
        }
    }

    void App::customInit() {

        Camera::setCamera(new Camera(LOOK_IN_DIRECTION,ORTOGONALE));
        //MODEL 1:
        Model* m1 = new Model("./src/Models/cube.obj",
                              "./src/Textures/cube.jpg",bufferManager);
        m1->init();
        m1->initDescriptor(&descManager);
        Mesh::meshes->push_back(m1);

        //MODEL 2:
        Model* m2 = new Model("./src/Models/rocket.obj",
                              "./src/Textures/rocket.jpg",bufferManager);
        m2->init();
        m2->initDescriptor(&descManager);
        Mesh::meshes->push_back(m2);
    }
}