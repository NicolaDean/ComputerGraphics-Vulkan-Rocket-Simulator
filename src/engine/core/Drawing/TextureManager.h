//
// Created by nicomane on 31/05/22.
//

#ifndef ROCKETSIMULATOR_TEXTUREMANAGER_H
#define ROCKETSIMULATOR_TEXTUREMANAGER_H
#pragma once
#include "../../commonLibs.h"

#include "BufferManager.h"

namespace Engine {
    VkImageView createImageView(VkDevice* device,VkImage image, VkFormat format,VkImageViewType type, VkImageAspectFlags aspectFlags,int layerCount);
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

        /**********************SKYBOX TEXTURE****************************/
        void createCubicTexture(std::string imageName);
        void createImageSkybox(uint32_t width, uint32_t height, VkImage &image,VkDeviceMemory &imageMemory);
        void createTextureImageViewSkybox();
        /*********************CREATE IMAGE METHOD**************************/
        void createTextureImage(std::string imageName);
        void createTextureImageView();
        void createTextureSampler();
        void createImage(uint32_t width, uint32_t height, VkFormat format,
                         VkImageTiling tiling, VkImageUsageFlags usage,
                         VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

        /***************UTILS******************************/
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout,int layerCount);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height,int layerCount);


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
