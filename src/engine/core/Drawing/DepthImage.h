//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DEPTHIMAGE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DEPTHIMAGE_H
#include "BufferManager.h"
#include "TextureManager.h"

namespace Engine{
    class DepthImage {
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;
        BufferManager bufferManager;

    public:
        DepthImage(){}
        DepthImage(BufferManager bufferMang){
            bufferManager = bufferMang;
        }

        void createDepthResources(VkExtent2D swapChainExtent,TextureManager textureManager);
        VkFormat findDepthFormat();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkImageView getDepthImageView(){
            return depthImageView;
        }

        void close(){
            vkDestroyImageView(*bufferManager.getAssignedDevice(), depthImageView, nullptr);
            vkDestroyImage(*bufferManager.getAssignedDevice(), depthImage, nullptr);
            vkFreeMemory(*bufferManager.getAssignedDevice(), depthImageMemory, nullptr);
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_DEPTHIMAGE_H
