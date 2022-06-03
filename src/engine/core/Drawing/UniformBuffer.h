//
// Created by nicomane on 30/05/22.
//

#ifndef ROCKETSIMULATOR_UNIFORMBUFFER_H
#define ROCKETSIMULATOR_UNIFORMBUFFER_H

#include "../Geometry/UniformBufferObject.h"
#include "../../commonLibs.h"
#include "../Utils/Constants.h"
#include "BufferManager.h"


namespace Engine {

    class UniformBuffer {
        /////UniformBuffer
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        VkDevice * device;
        BufferManager bufferManager;

    public:
        UniformBuffer(){};
        UniformBuffer(VkDevice * dev){
            device = dev;
        };

        UniformBuffer(BufferManager bufferMng){
            device = bufferMng.getAssignedDevice();
            bufferManager = bufferMng;
        };

        void close();
        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage,VkExtent2D swapChainExtent);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                     VkDeviceMemory &bufferMemory);


        //GETTER:
        std::vector<VkBuffer> getUniformBuffer(){
            return uniformBuffers;
        }

        std::vector<VkBuffer> *  getUniformBufferRef(){
            return &uniformBuffers;
        }

        std::vector<VkDeviceMemory> getUniformBufferMemory(){
            return uniformBuffersMemory;
        }

    };
}


#endif //ROCKETSIMULATOR_UNIFORMBUFFER_H
