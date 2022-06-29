//
// Created by nicomane on 29/06/22.
//

#include "Map.h"

namespace Engine
{
    Map* Map::singleton_map = new Map();


    void Map::populateMapWithRandomObject(DescriptorManager *manager, GraphicPipelineCustom *pipelineCustom) {
        std::vector<Model*> models = cactusPools.generatePool(100);
        cactusPools.initModels(pipelineCustom,manager);

        for(auto m : models){
            float x,y;

            x = ((float)rand() / (float)RAND_MAX) * 2 - 1;
            y = ((float)rand() / (float)RAND_MAX) * 2 - 1;

            x = x * (SIZE/2);
            y = y * (SIZE/2);

            std::cout<<std::dec<<"("<<x<<","<<y<<")\n";
            int h = this->getHeight(x,y);

            m->setPos(glm::vec3(x,h,y));
            m->setScale(0.1);
        }
    }
}