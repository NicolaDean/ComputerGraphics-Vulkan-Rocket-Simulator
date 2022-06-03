//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_TEXTURE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_TEXTURE_H
#include "../../commonLibs.h"
#include "../Drawing/TextureManager.h"
#include "../Drawing/BufferManager.h"

namespace Engine{
    class Texture {
        TextureManager textureManager;
        std::string name;

    public:
        Texture(){}
        Texture(std::string n,BufferManager bufferMng ){
            name = n;
            textureManager = TextureManager(bufferMng);
        }

        void load(){
            textureManager.createTextureImage(name);
            textureManager.createTextureImageView();
            textureManager.createTextureSampler();
        }

        void clean(){
            textureManager.close();
        }

        VkSampler getSampler(){return textureManager.getSampler();};
        VkImageView getImageView(){return textureManager.getImageView();};

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_TEXTURE_H
