//
// Created by nicomane on 11/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLANE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLANE_H

#include "../../engine/core/Objects/Mesh.h"

namespace Engine {
    class Plane : public Mesh {
    protected:


        int resolutionX;
        int resolutionY;

    public:
        int SIZE;
        Plane(){};
        Plane(int size,int resX,int resY,BufferManager buffManager) : Mesh(buffManager) {
            SIZE = size;
            resolutionX = resX;
            resolutionY = resY;
        };

        void generatePlane();

        virtual float getHeight(int x, int y)=0;
        virtual glm::vec3 getColor(int x, int y)=0;

        void init();

    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLANE_H
