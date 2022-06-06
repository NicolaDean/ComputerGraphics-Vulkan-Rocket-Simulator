//
// Created by nicomane on 02/06/22.
//

#include "App.h"

namespace Engine{

    void App::updateScene(uint32_t currentImage) {
        //DO ONE CYCLE FOR SIMPLY RENDER THINGS AND BEFORE THAT A CYCLE THAT UPDATE ALL THE DYNAMIC OBJECT POSITION(only movable objects)
        for (auto mesh : *Mesh::meshes) //TODO ACCESS "MOVABLE OBJECTS IN A SEPARATE LOOP"
        {
            if(glfwGetKey(window, GLFW_KEY_A)) {
                mesh->move();
            }

            if(glfwGetKey(window, GLFW_KEY_S)) {
                Camera::setCamera(new Camera(LOOK_AT_CAMERA,ORTOGONALE));
            }
            if(glfwGetKey(window, GLFW_KEY_W)) {
                Camera::setCamera(new Camera());
            }
            //TODO HERE PUT INPUTS AND CALL THE MESHES METHODS
            mesh->updateUniformBuffer(currentImage);
        }
    }

    void App::customInit() {
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