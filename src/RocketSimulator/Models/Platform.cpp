//
// Created by Marco Fasanella on 03/07/22.
//

#include "Platform.h"
#include "../../engine/core/Core.h"

#include <stdio.h>
#include <math.h>

namespace Engine {

    void Platform::update(float dt) {
        GLFWwindow* window=Core::getWindow();
        if (Platform::target) {
            if (glfwGetKey(window, GLFW_KEY_I)) {
                onI(dt);
            }
            if (glfwGetKey(window, GLFW_KEY_K)) {
                onK(dt);
            }
            if (glfwGetKey(window, GLFW_KEY_L)) {
                onL(dt);
            }
            if (glfwGetKey(window, GLFW_KEY_J)) {
                onJ(dt);
            }

        }

    }

    void Platform::onI(float dt) {
        pos[0] += speed * pos[0] * dt;
        //pos[1]= ProceduratTerrain::getHeight(pos[0],pos[1]);
    }

    void Platform::onJ(float dt) {
        pos[2] += -speed * pos[2] * dt;
    }

    void Platform::onK(float dt) {
        pos[0] += -speed * pos[0] * dt;
    }

    void Platform::onL(float dt) {
        pos[2] += speed *pos[2] * dt;
    }




    }
