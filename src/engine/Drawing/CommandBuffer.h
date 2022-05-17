#ifndef ENGINE_COMMANDBUFFER_H
#define ENGINE_COMMANDBUFFER_H

#pragma once
#include "../commonLibs.h"
#include "../GraphicPipeline/GraphicPipeline.h"
#include "../Presentation/SwapChain.h"
#include "FrameBuffer.h"
#include "../Utils/Constants.h"
namespace Engine{
    //TODO THIS CLASS MUST BE UPDATED WITH SOME "CUSTOMIZABLE" CREATE COMMAND FUNCTIONS (Now they are hardcoded)
    class CommandBuffer {
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkDevice* device;
        FrameBuffer* frameBuffer;

    public:
        CommandBuffer(){

        }
        CommandBuffer(VkDevice* dev,FrameBuffer* buffer){
            device = dev;
            frameBuffer = buffer;
        }

        std::vector<VkCommandBuffer> getCommandBuffer(){
            return commandBuffers;
        }
        void init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void close();
        void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void createCommandBuffer();
        void recordCommandBuffer(int currFrame, uint32_t imageIndex,SwapChain swapChain,GraphicPipeline graphicPipeline);

    };
}
#endif //ENGINE_COMMANDBUFFER_H