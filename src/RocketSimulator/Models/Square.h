//
// Created by nicomane on 08/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SQUARE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SQUARE_H

#include "../../engine/core/Objects/Mesh.h"

namespace Engine{
    class Square: public Mesh{

    public:
        Square(BufferManager buffManager):Mesh(buffManager){
            //TODO AUTOGENERATE
            vertices ={
                    {{-5.0f,-5.0f,0.0f},{1.0f,0.0f,0.0f},{1,0}},
                    {{5.0f,-5.0f,0.0f},{1.0f,0.0f,0.0f},{1,0}},
                    {{5.0f,5.0f,0.0f},{0.0f,1.0f,0.0f},{1,1}},
                    {{-5.0f,5.0f,0.0f},{0.0f,1.0f,0.0f},{0,0}},
                };

            indices = {0, 1, 2, 2, 3, 0};
        }

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SQUARE_H
