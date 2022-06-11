//
// Created by nicomane on 11/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLANE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLANE_H

#include "../../engine/core/Objects/Mesh.h"

namespace Engine {
    class Plane : public Mesh {
        int width;
        int height;

        int resolutionX;
        int resolutionY;

    public:
        Plane(int x, int y,int resX,int resY,BufferManager buffManager) : Mesh(buffManager) {
            width = x;
            height = y;
            resolutionX = resX;
            resolutionY = resY;
        };

        void generatePlane();

        void init();

    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PLANE_H
