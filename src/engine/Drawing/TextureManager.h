//
// Created by nicomane on 31/05/22.
//

#ifndef ROCKETSIMULATOR_TEXTUREMANAGER_H
#define ROCKETSIMULATOR_TEXTUREMANAGER_H
#pragma once
#include "../commonLibs.h"

#include "BufferManager.h"

namespace Engine {
    VkImageView createImageView(VkDevice* device,VkImage image, VkFormat format);
    class TextureManager {

        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;

        BufferManager bufferManager;
    public:
        TextureManager() {

        }

        TextureManager(BufferManager bufferMng) {
            bufferManager = bufferMng;
        }

        void close();
        void createTextureImage();
        void createTextureImageView();
        void createTextureSampler();
        //UTILS FUNCTIONS:
        void
        createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);


        //Getter
        VkSampler getSampler(){
            return textureSampler;
        }
        VkImageView getImageView(){
            return textureImageView;
        }
    };

}

#endif //ROCKETSIMULATOR_TEXTUREMANAGER_H
