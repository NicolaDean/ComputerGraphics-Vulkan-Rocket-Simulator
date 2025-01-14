//
// Created by nicomane on 19/06/22.
//

#include "UIcomponent.h"
#include <stdio.h>

#if defined(__linux__) // any linux distribution
#define PLATFORM "linux"
#elif defined(_WIN32) // any windows system
#define PLATFORM "windows"
#else
#define PLATFORM "Is not linux or windows"
#endif

namespace Engine{

    bool UIcomponent::isClicked(float X, float Y) {

        float screen_width = SwapChain::getSwapChainExtent().width;
        float screen_height = SwapChain::getSwapChainExtent().height;


        //NORMALIZE COORDINATE (Where MIN is 0 and MAX is screen_max_size)
        //https://stats.stackexchange.com/questions/281162/scale-a-number-between-a-range
        float x ;
        float y ;
        //Check for OS
            if((std::string )PLATFORM=="linux"||(std::string )PLATFORM=="windows"){
                x = (2.0f * X) / (screen_width) - 1.0f;
                y =  (2.0f * Y) / (screen_height) -1.0f;
            }else{
                x = (2.0f * X) / (screen_width/2) - 1.0f;
               y =  (2.0f * Y) / (screen_height/2) -1.0f;
            }

        //horizontal    interval ( minX < x < maxX)
        float minX = x_pos - width/(float)2;
        float maxX = x_pos + width/(float)2;
        //vertical      interval (minY < y <maxY)
        float minY = y_pos - height/(float)2;
        float maxY = y_pos + height/(float)2;

        //std::cout<<"X:("<<minX<<" <" << x << " <" << maxX <<")\n";
        //std::cout<<"X:"<<X<<" ,Y:" << Y << " ," << screen_width   <<" ," <<screen_height <<"\n";

        //std::cout<<"Y:("<<minY<<" <" << y << " <" << maxY <<")\n";
        //Result initialize
        bool betweenX = false;
        bool betweenY = false;

        //Check if point inside intervals
        if(x>minX && x<maxX) betweenX = true;
        if(y>minY && y<maxY) betweenY = true;

        bool clicked = betweenX && betweenY;
        if(clicked){
            std::cout<<"Clicked\n";
            action();
        }
        //Return true if point inside rectangle
        return clicked;
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
        std::cout<<"WIDTH: "<<w<<"\n";

        //WRITE VERTEX IN COUNTER CLOCKWISE ORDER
        vertices.push_back(Vertex::vertexFactory(-w+x,h+y,0,0.0f,1.0f,0.0f,0,1));
        vertices.push_back(Vertex::vertexFactory(w+x,h+y,0,0.0f,1.0f,0.0f,1,1));
        vertices.push_back(Vertex::vertexFactory(w+x,-h+y,0,1.0f,0.0f,0.0f,1,0));
        vertices.push_back(Vertex::vertexFactory(-w+x,-h+y,0,1,0,0,0,0));
    }
}