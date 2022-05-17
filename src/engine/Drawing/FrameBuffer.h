#include "../commonLibs.h"
#pragma once
namespace Engine{

    class FrameBuffer {
        std::vector<VkFramebuffer> swapChainFramebuffers;

    public:
        FrameBuffer(){}

        VkFramebuffer getSwapChainFramebuffers(int index){
                return swapChainFramebuffers[index];
        }
        void close(VkDevice device);
        void createFrameBuffer(VkDevice device,std::vector<VkImageView> swapChainImageViews,VkExtent2D swapChainExtent,VkRenderPass renderPass);
    };
}



