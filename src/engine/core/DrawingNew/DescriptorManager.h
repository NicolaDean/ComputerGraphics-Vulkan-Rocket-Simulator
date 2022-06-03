//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DESCRIPTORMANAGER_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DESCRIPTORMANAGER_H
#include "../../commonLibs.h"
#include "../GraphicPipeline/Descriptor.h"
#include "UniformBufferManager.h"
#include "../Objects/Texture.h"
#include "../Presentation/SwapChain.h"
#include "../Drawing/BufferManager.h"

namespace Engine{

    struct DescriptorSetLayoutBinding {
        uint32_t binding;
        VkDescriptorType type;
        VkShaderStageFlags flags;
    };
    enum DescriptorSetElementType {UNIFORM, TEXTURE};

    struct DescriptorSetElement {
        int binding;
        DescriptorSetElementType type;
        int size;
        Texture *tex;
    };

    class DescriptorManager {
        //Descriptors user info  vector
        std::vector<DescriptorSetElement> elementsDescriptors;
        std::vector<DescriptorSetLayoutBinding> bindingsDescriptors;
        //Helper
        VkDevice * device;
        UniformBufferManager uniformBufferManager;

        std::vector<std::vector<VkBuffer>> uniformBuffers;
        std::vector<std::vector<VkDeviceMemory>> uniformBuffersMemory;

        //Descriptors
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        SwapChain * swapChain;
        BufferManager bufferManager;
    public:

        DescriptorManager(){}
        DescriptorManager(BufferManager manager,SwapChain * swap){
            bufferManager = manager;
            device = manager.getAssignedDevice();
            swapChain = swap;
            uniformBufferManager = UniformBufferManager(manager);
        }

        //User push descriptors info
        void pushElementDescriptor(DescriptorSetElement e){elementsDescriptors.push_back(e);};
        void pushBindingDescriptor(DescriptorSetLayoutBinding b){bindingsDescriptors.push_back(b);};

        //Create Descriptors
        void createDescriptorSetLayouts();
        void createDescriptorPool();
        void createDescriptorSets();


        //Getter
        VkDescriptorSetLayout getDescriptorSetLayout(){
            return descriptorSetLayout;
        }
        std::vector<VkDescriptorSet> getDescriptorSet(){
            return descriptorSets;
        }

        void updateBufferManager(uint32_t currentImage){
            uniformBufferManager.update(currentImage,swapChain->getSwapChainExtent());
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DESCRIPTORMANAGER_H
