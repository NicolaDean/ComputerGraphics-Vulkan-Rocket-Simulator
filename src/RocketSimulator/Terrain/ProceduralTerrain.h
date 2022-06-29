//
// Created by nicomane on 12/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PROCEDURALTERRAIN_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PROCEDURALTERRAIN_H


#include "Plane.h"
#include "../Utils/ColorGradient.h"
#include "../Utils/PerlinNoise.h"
#include "../Utils/Random3DModelPool.h"

namespace Engine{
    class ProceduralTerrain:public Plane {

        int seed = 2222;
        PerlinNoise noises = PerlinNoise();
        Random3DModelPool cactusPools = Random3DModelPool();
        Random3DModelPool rockPools   = Random3DModelPool();
        std::vector<Model*> cactus;
        float * heights; //TODO use dynamic programming to avoid recomputing same height multiple times


    public:
        ProceduralTerrain(): Plane(){};
        ProceduralTerrain(int size,int resX,int resY,BufferManager buffManager) : Plane(size,resX,resY,buffManager){
            noises = PerlinNoise(resX,resY);
            noises.setSeed(seed); //TODO PUT A BUTTON THAT CHANGE SEED
            noises.init();
            noises.generate2DPerlinNoise(5);

            cactusPools = Random3DModelPool(resX,resY,{ "./src/Models/Desert/aloe.obj",
                                                            "./src/Models/Desert/cactus01.obj",
                                                            "./src/Models/Desert/cactus02.obj",
                                                            "./src/Models/Desert/cactus03.obj"},buffManager);
            cactusPools.init();
            cactusPools.generatePool(10);

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
