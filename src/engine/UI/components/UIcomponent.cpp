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

    void UIcomponent::initVertices(float x, float y, float w, float h) {
        /*vertices.push_back(Vertex::vertexFactory(-w,-h,-(near_plane),1,0,0,1,1));
        vertices.push_back(Vertex::vertexFactory(w,-h,-(near_plane),1,0,0,0,1));
        vertices.push_back(Vertex::vertexFactory(w,h,-(near_plane),1,0,0,0,0));
        vertices.push_back(Vertex::vertexFactory(-w,h,-(near_plane),1,0,0,1,0));
        */



        std::cout<<"WIDTH: "<<w<<"\n";

        vertices.push_back(Vertex::vertexFactory(-w+x,-h+y,-(0.2),1,0,0,1,1));
        vertices.push_back(Vertex::vertexFactory(w+x,-h+y,-(0.2),1.0f,0.0f,0.0f,0,1));
        vertices.push_back(Vertex::vertexFactory(w+x,h+y,-(0.2),0.0f,1.0f,0.0f,0,0));
        vertices.push_back(Vertex::vertexFactory(-w+x,h+y,-(0.2),0.0f,1.0f,0.0f,1,0));
    }
}