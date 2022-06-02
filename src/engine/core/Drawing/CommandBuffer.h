#ifndef ENGINE_COMMANDBUFFER_H
#define ENGINE_COMMANDBUFFER_H

#pragma once
#include "../../commonLibs.h"
#include "../GraphicPipeline/GraphicPipeline.h"
#include "../Presentation/SwapChain.h"
#include "FrameBuffer.h"
#include "VertexBuffer.h"
#include "../Utils/Constants.h"
namespace Engine{
    //TODO THIS CLASS MUST BE UPDATED WITH SOME "CUSTOMIZABLE" CREATE COMMAND FUNCTIONS (Now they are hardcoded)
    class CommandBuffer {
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkDevice* device;
        FrameBuffer* frameBuffer;
        VertexBuffer* vertexBuffer;

    public:
        CommandBuffer(){

        }
        CommandBuffer(VkDevice* dev,FrameBuffer* buffer,VertexBuffer* vertexBuff){
            device = dev;
            frameBuffer = buffer;
            vertexBuffer = vertexBuff;
        }

        std::vector<VkCommandBuffer> getCommandBuffer(){
            return commandBuffers;
        }

        void init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void close();
        void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void createCommandBuffer();
        void recordCommandBuffer(int currFrame, uint32_t imageIndex,SwapChain swapChain,GraphicPipeline graphicPipeline);


        VertexBuffer* getVertexBuffer(){
            return vertexBuffer;
        }

        VkCommandPool getCommandPool(){
            return commandPool;
        }
        VkCommandPool * getCommandPoolRef(){
            return &commandPool;
        }
    };
}
#endif //ENGINE_COMMANDBUFFER_H