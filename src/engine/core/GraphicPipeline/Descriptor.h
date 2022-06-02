//
// Created by nicomane on 30/05/22.
//

#ifndef ROCKETSIMULATOR_DESCTIPTOR_H
#define ROCKETSIMULATOR_DESCTIPTOR_H
#include "../../commonLibs.h"
#include "../Utils/Constants.h"
#include "../Drawing/UniformBuffer.h"
#include "../Drawing/TextureManager.h"

namespace Engine{
    class Descriptor {
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        VkDevice* device;

    public:
        Descriptor(){}
        Descriptor(VkDevice* dev){
            device = dev;
        }
        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets(UniformBuffer * uniformBuffer,TextureManager textureManager);
        void close();

        //GETTER
        VkDescriptorSetLayout* getDescriptorSetLayout(){
            return &descriptorSetLayout;
        }

        std::vector<VkDescriptorSet> getDescriptorSets(){
            return descriptorSets;
        }
    };
}



#endif //ROCKETSIMULATOR_DESCTIPTOR_H
