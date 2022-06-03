//
// Created by nicomane on 02/06/22.
//

#include "UniformBufferManager.h"

namespace Engine{
    void UniformBufferManager::pushUniformBuffer(){
        UniformBuffer buffer = UniformBuffer(bufferManager);
        buffer.createUniformBuffers();
        uniformBuffers.push_back(buffer);

        //return &buffer; //TODO Check if pointer is ok
    }

    VkBuffer UniformBufferManager::getBuffer(int buffer,int frame) {
        return uniformBuffers[buffer].getUniformBuffer()[frame];
    }

    void UniformBufferManager::update(uint32_t currentImage,VkExtent2D swapChainExtent) {
        //UPDATE UNIFORM BUFFER OF ALL DESCRIPTOR SETS
        for(int i=0;i<uniformBuffers.size();i++){
            uniformBuffers[i].updateUniformBuffer(currentImage,swapChainExtent);
        }
    }

    void UniformBufferManager::clean() {
        for(int i=0;i<uniformBuffers.size();i++){
            uniformBuffers[i].close();
        }
    }
}
