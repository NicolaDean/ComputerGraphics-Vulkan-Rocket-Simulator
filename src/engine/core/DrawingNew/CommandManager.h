//
// Created by nicomane on 03/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COMMANDMANAGER_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COMMANDMANAGER_H
#include "../../commonLibs.h"
#include "../Drawing/FrameBuffer.h"
#include "GraphicPipelineCustom.h"
#include "../Objects/Mesh.h"
#include "../Objects/Model.h"
#include "../../UI/UImanager.h"
namespace Engine{
    class CommandManager {
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkDevice* device;
        FrameBuffer* frameBuffer;
        GraphicPipelineCustom*  graphicPipeline;
        Model M1;
        Model M2;
        DescriptorManager * descriptorManager;
        DescriptorManager * globalDescriptor;

    public:

        CommandManager(){}
        CommandManager(VkDevice * dev){
            device = dev;
        }

        CommandManager(VkDevice * dev,FrameBuffer * buff,GraphicPipelineCustom * pipeline){
            device = dev;
            frameBuffer = buff;
            graphicPipeline = pipeline;
        }


        void close();
        void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void createCommandBuffers();
        void recordCommandBuffers();
        void recordCommandBuffer(int currentImage);
        void populateCommandBuffers(int currentImage,std::vector<Mesh*> meshes);
        void populateUIcommandBuffers(int currentImage);

        void setModel(Model m1){
            M1 = m1;
        }

        VkCommandPool getCommandPool(){
            return commandPool;
        }

        void setFrameBuffer(FrameBuffer * buff){
            frameBuffer = buff;
        }

        void setGraphicPipeline(GraphicPipelineCustom * pipeline){
            graphicPipeline = pipeline;
        }

        void setDescriptor(DescriptorManager * descriptorMng){
            descriptorManager = descriptorMng;
        }
        void setGlobalDescriptor(DescriptorManager * descriptorMng){
            globalDescriptor = descriptorMng;
        }
        std::vector<VkCommandBuffer> getCommandBuffers(){
            return commandBuffers;
        }

        VkCommandBuffer * getCommandBuffers(int imageIndex){
            return &(commandBuffers[imageIndex]);
        }

        void updateBufferManager(uint32_t currentImage){
            descriptorManager->updateBufferManager(currentImage);
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COMMANDMANAGER_H
