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

    enum uniformsType {UNIFORM_B,GLOBAL_UNIFORM_B};
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

        //Descriptors
        std::vector<VkDescriptorSet> descriptorSets;
        VkDescriptorSetLayout descriptorSetLayout;

        SwapChain * swapChain;
        BufferManager bufferManager;
    public:
        static int MAX_NUM_OF_ENTITY; //TODO ADD AN EXEPTION IN DESCRIPTOR SET TO AVOID ENTITY OVERFLOW
        static DescriptorManager* globalDescriptor;
        static VkDescriptorPool descriptorPool; //STATIC BECAUSE ALL DESCRIPTOR USE SAME DESCRIPTOR POOL


        DescriptorManager(){}
        DescriptorManager(BufferManager manager,SwapChain * swap){
            bufferManager = manager;
            device = manager.getAssignedDevice();
            swapChain = swap;
            uniformBufferManager = UniformBufferManager(manager);
        }

        void close();
        void closeDescriptorPool();
            void setAsGlobal();
        static void setAsGlobal(DescriptorManager* d);

        //User push descriptors info
        void pushElementDescriptor(DescriptorSetElement e){elementsDescriptors.push_back(e);};
        void pushBindingDescriptor(DescriptorSetLayoutBinding b){bindingsDescriptors.push_back(b);};

        //Create Descriptors
        void createDescriptorSetLayouts();
        void createDescriptorPool(VkDevice* device);
        std::vector<VkDescriptorSet> createAndGetDescriptorSets(UniformBufferManager* manager);
        void createDescriptorSets();

        //Getter
        VkDescriptorSetLayout getDescriptorSetLayout(){
            return descriptorSetLayout;
        }
        std::vector<VkDescriptorSet> getDescriptorSet(){
            return descriptorSets;
        }
        DescriptorManager * getGlobalDescriptor(){
            return globalDescriptor;
        }
        void updateBufferManager(uint32_t currentImage){
            uniformBufferManager.update(currentImage,glm::mat4(1.0f));//TODO CORRECT HERE IF NEDED
        }

        static void set_MAX_NUM_OF_ENTITY(int max){
            DescriptorManager::MAX_NUM_OF_ENTITY = max;
        }

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DESCRIPTORMANAGER_H
