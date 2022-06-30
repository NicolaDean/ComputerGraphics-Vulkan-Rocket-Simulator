//
// Created by nicomane on 29/06/22.
//

#include "Map.h"

namespace Engine
{
    Map* Map::singleton_map = new Map();


    void Map::positionModel(Model *m) {
        float grid_x,grid_y;

        grid_x = ((float)rand() / (float)RAND_MAX) * resolutionX;
        grid_y = ((float)rand() / (float)RAND_MAX) * resolutionY;

        float posX = ((float)grid_x/((float)resolutionX -1)) * SIZE;
        float posY = ((float)grid_y/((float)resolutionY -1)) * SIZE;
        float h = ProceduralTerrain::getHeight(posX,posY);

        std::cout<<std::dec<<"("<<posX<<","<<posY<<","<<h<<")\n";


        m->setPos(glm::vec3(posX - SIZE/2,h,posY- SIZE/2));
        m->setScale(0.5);
    }
    void Map::populateMapWithRandomObject(DescriptorManager *manager, GraphicPipelineCustom *pipelineCustom) {
        cactusPools.generatePool(200);
        std::vector<Model*> models =  cactusPools.initModels(pipelineCustom,manager);

        for(auto m : models){
            positionModel(m);
        }

        rockPools.generatePool(30);
        std::vector<Model*> rocks =  rockPools.initModels(pipelineCustom,manager);

        for(auto m : rocks){
            positionModel(m);
        }
    }
}