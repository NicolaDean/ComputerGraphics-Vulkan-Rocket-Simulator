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
namespace Engine{
    class CommandManager {
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkDevice* device;
        FrameBuffer* frameBuffer;
        GraphicPipelineCustom*  graphicPipeline;
        Model M1;
        DescriptorManager * descriptorManager;

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


        void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void createCommandBuffers();
        void recordCommandBuffers();
        void populateCommandBuffers(VkCommandBuffer commandBuffer, int currentImage);

        void setModel(Model m){
            M1 = m;
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

        std::vector<VkCommandBuffer> getCommandBuffers(){
            return commandBuffers;
        }

        void updateBufferManager(uint32_t currentImage){
            descriptorManager->updateBufferManager(currentImage);
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COMMANDMANAGER_H
