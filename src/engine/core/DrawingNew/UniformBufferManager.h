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
        //std::vector<std::vector<VkBuffer>> uniformBuffers;
        BufferManager bufferManager;

    public:
        UniformBufferManager(){}
        UniformBufferManager(BufferManager bufferMng){
            bufferManager = bufferMng;
        }

        void clean();
        void pushUniformBuffer(int i);

        void resizeVector(int size){
            uniformBuffers.resize(size);
        }

        std::vector<UniformBuffer> * getBuffers(){
            return &uniformBuffers;
        }
        VkBuffer getBuffer(int buffer,int frame) {
            return (uniformBuffers[buffer].getUniformBuffer())[frame];
        }

        std::vector<VkBuffer>   getBuffer(int buffer){
            return (uniformBuffers[buffer].getUniformBuffer());
        }

        void update(uint32_t currentImage,VkExtent2D swapChainExtent);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UNIFORMBUFFERMANAGER_H
