//
// Created by nicomane on 29/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MAP_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MAP_H
#include "./ProceduralTerrain.h"
namespace Engine{
    class Map:public ProceduralTerrain {

        static Map* singleton_map;

    public:
        Map(): ProceduralTerrain(){}
        Map(int size,int resX,int resY,BufferManager buff): ProceduralTerrain(size,resX,resY,buff){
            if(singleton_map != nullptr) free(singleton_map);
            singleton_map = this;
        }

        static float getMapHeight(int x, int z){
            return 4;
            //singleton_map->getHeight(x,z); // TODO UNDERSTAND HOW GET THE MAP HEIGHT FROM COORDINATES
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MAP_H
