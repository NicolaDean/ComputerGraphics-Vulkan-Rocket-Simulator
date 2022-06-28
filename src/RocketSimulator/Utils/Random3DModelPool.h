//
// Created by nicomane on 25/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_RANDOM3DMODELPOOL_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_RANDOM3DMODELPOOL_H
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "../../src/engine/core/Objects/Model.h"

namespace Engine{
    class Random3DModelPool {

        int width;
        int height;

        int SEED;
        std::vector<std::string> modelPaths;
        BufferManager bufferManager;
    public:
        Random3DModelPool(){};

        Random3DModelPool(int x,int y,std::vector<std::string> mp,BufferManager buff){
            width = x;
            height = y;
            modelPaths = mp;
            bufferManager = buff;

        }

        void init();
        void initModels(GraphicPipelineCustom pipeline,DescriptorManager descriptor);
        std::vector<Model*> generatePool(int poolSize);
        void setSeed(int seed){
            SEED = seed;
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_RANDOM3DMODELPOOL_H
