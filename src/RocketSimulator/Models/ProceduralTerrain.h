//
// Created by nicomane on 12/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PROCEDURALTERRAIN_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PROCEDURALTERRAIN_H


#include "Plane.h"
#include "../Utils/ColorGradient.h"
namespace Engine{
    class ProceduralTerrain:public Plane {

        int seed = 11111;
    public:
        ProceduralTerrain(int size,int resX,int resY,BufferManager buffManager) : Plane(size,resX,resY,buffManager){

        }

        float getHeight(int x, int y);
        float getNoise(int x,int y);
        float terrainSmoothing(int x,int y);
        void close();
        float getHeightMod(int x, int z);
        glm::vec3 calculateNormal(int x, int z);
        glm::vec3 getColor(int x,int y);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PROCEDURALTERRAIN_H
