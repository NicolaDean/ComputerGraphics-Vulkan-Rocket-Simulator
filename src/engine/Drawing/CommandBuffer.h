#ifndef ENGINE_CommandBuffer_H
#define ENGINE_CommandBuffer_H

#pragma once
#include "../commonLibs.h"
#include "../GraphicPipeline/GraphicPipeline.h"
#include "../Presentation/SwapChain.h"
#include "FrameBuffer.h"
namespace Engine{
    //TODO THIS CLASS MUST BE UPDATED WITH SOME "CUSTOMIZABLE" CREATE COMMAND FUNCTIONS (Now they are hardcoded)
    class CommandBuffer {
        VkCommandPool commandPool;
        VkCommandBuffer commandBuffer;
        VkDevice* device;
        FrameBuffer* frameBuffer;

    public:
        CommandBuffer(){

        }
        CommandBuffer(VkDevice* dev,FrameBuffer* buffer){
            device = dev;
            frameBuffer = buffer;
        }

        VkCommandBuffer getCommandBuffer(){
            return commandBuffer;
        }
        void init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void close();
        void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void createCommandBuffer();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,SwapChain swapChain,GraphicPipeline graphicPipeline);

    };
}
#endif //ENGINE_A_H