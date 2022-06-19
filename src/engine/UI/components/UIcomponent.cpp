//
// Created by nicomane on 19/06/22.
//

#include "UIcomponent.h"

namespace Engine{


    bool UIcomponent::isClicked(float x, float y) {
        //horizontal    interval ( minX < x < maxX)
        float minX = x_pos - width/(float)2;
        float maxX = x_pos + width/(float)2;
        //vertical      interval (minY < y <maxY)
        float minY = y_pos - height/(float)2;
        float maxY = y_pos + height/(float)2;

        //Result initialize
        bool betweenX = false;
        bool betweenY = false;

        //Check if point inside intervals
        if(x>minX && x<maxX) betweenX = true;
        if(y>minY && y<maxY) betweenY = true;

        //Return true if point inside rectangle
        return betweenX && betweenY;
    }

    void UIcomponent::init() {
        texture.load();
        Mesh::init();
    }

    void UIcomponent::initDescriptor(DescriptorManager* descriptorManager) {
        descriptorManager->pushElementDescriptor({0, UNIFORM, sizeof(UniformBufferObject), nullptr});
        descriptorManager->pushElementDescriptor({1, TEXTURE, 0, &texture});
        descriptorSets = descriptorManager->createAndGetDescriptorSets(&uniformBufferManager);
    }

    void UIcomponent::close() {
        Mesh::close();
        texture.clean();
    }
}