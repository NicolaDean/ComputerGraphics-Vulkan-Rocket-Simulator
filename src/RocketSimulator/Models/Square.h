//
// Created by nicomane on 08/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SQUARE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SQUARE_H

#include "../../engine/core/Objects/Mesh.h"
#include "../../engine/core/Objects/Texture.h"

namespace Engine{
    class Square: public Mesh{

        Texture texture;
    public:
        Square(BufferManager buffManager):Mesh(buffManager){
            //TODO AUTOGENERATE
            vertices ={
                    {{-0.5f,-0.5f,-3.0f},{1.0f,0.0f,0.0f},{1.0f, 0.0f, 0.0f},{1,1}},
                    {{0.5f,-0.5f,-3.0f},{1.0f,0.0f,0.0f},{1.0f, 0.0f, 0.0f},{0,1}},
                    {{0.5f,0.5f,-3.0f},{0.0f,1.0f,0.0f},{1.0f, 0.0f, 0.0f},{0,0}},
                    {{-0.5f,0.5f,-3.0f},{0.0f,1.0f,0.0f},{1.0f, 0.0f, 0.0f},{1,0}},
                };

            indices = {0, 1, 2, 2, 3, 0};
            texture = Texture("./src/Textures/desert.jpeg",buffManager);
        }

        void initDescriptor(DescriptorManager* descriptorManager) {
            descriptorManager->pushElementDescriptor({0, UNIFORM, sizeof(UniformBufferObject), nullptr});
            descriptorManager->pushElementDescriptor({1, TEXTURE, 0, &texture});
            descriptorSets = descriptorManager->createAndGetDescriptorSets(&uniformBufferManager);
        }
        void init(){texture.load();Mesh::init();}
        void close(){Mesh::close();}

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SQUARE_H
