//
// Created by Marco Fasanella on 03/07/22.
//

#include "Platform.h"
#include "../../engine/core/Core.h"
#include "../Terrain/ProceduralTerrain.h"
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

            //y = height of map in (x,z)
            pos[1] = Map::getMapHeight(pos[0],pos[2]);
        }

    }

    //TODO the target then is slow
    void Platform::onI(float dt) {
        //pos[0] += speed * pos[0] * dt;
        pos[0] +=  speed * dt;

    }

    void Platform::onJ(float dt) {
        //pos[2] += -speed * pos[2] * dt;
        pos[2] +=  -speed  * dt;

    }

    void Platform::onK(float dt) {
       // pos[0] += -speed * pos[0] * dt;
        pos[0] +=  -speed  * dt;

    }

    void Platform::onL(float dt) {
        //pos[2] += speed *pos[2] * dt;
        pos[2] += speed  * dt;

    }




    }
