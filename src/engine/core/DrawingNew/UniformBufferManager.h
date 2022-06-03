//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UNIFORMBUFFERMANAGER_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UNIFORMBUFFERMANAGER_H
#include "../../commonLibs.h"
#include "../Drawing/UniformBuffer.h"
#include "../Drawing/BufferManager.h"

namespace Engine{
    class UniformBufferManager {
        std::vector<UniformBuffer> uniformBuffers;
        BufferManager bufferManager;

    public:
        UniformBufferManager(){}
        UniformBufferManager(BufferManager bufferMng){
            bufferManager = bufferMng;
        }

        void clean();
        void pushUniformBuffer();
        VkBuffer getBuffer(int buffer,int frame) ;

        void update(uint32_t currentImage,VkExtent2D swapChainExtent);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UNIFORMBUFFERMANAGER_H
