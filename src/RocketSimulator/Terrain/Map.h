//
// Created by nicomane on 29/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MAP_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MAP_H
#include "./ProceduralTerrain.h"
#include "../Utils/Random3DModelPool.h"
#include "../../engine/core/Objects/Model.h"

namespace Engine{
    class Map:public ProceduralTerrain {

        static Map* singleton_map;

        Random3DModelPool cactusPools = Random3DModelPool();
        Random3DModelPool rockPools   = Random3DModelPool();
        std::vector<Model*> cactus;

    public:
        Map(): ProceduralTerrain(){}
        Map(int size,int resX,int resY,BufferManager buff): ProceduralTerrain(size,resX,resY,buff){
            if(singleton_map != nullptr) free(singleton_map);
            singleton_map = this;

            cactusPools = Random3DModelPool(resX,resY,{ "./src/Models/Desert/aloe.obj",
                                                        "./src/Models/Desert/cactus01.obj",
                                                        "./src/Models/Desert/cactus02.obj",
                                                        "./src/Models/Desert/cactus03.obj"},buff);
            cactusPools.init();
        }

        void populateMapWithRandomObject(DescriptorManager* manager, GraphicPipelineCustom* pipelineCustom);
        static float getMapHeight(int x, int z){
            return 4;
            //singleton_map->getHeight(x,z); // TODO UNDERSTAND HOW GET THE MAP HEIGHT FROM COORDINATES
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MAP_H
