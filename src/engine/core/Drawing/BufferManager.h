//
// Created by nicomane on 30/05/22.
//

#ifndef ROCKETSIMULATOR_BUFFERMANAGER_H
#define ROCKETSIMULATOR_BUFFERMANAGER_H
#include "../../commonLibs.h"
#include "../Device/LogicDeviceManager.h"

namespace Engine{
    class BufferManager {

        VkDevice * device;
        VkPhysicalDevice physicalDevice;
        LogicDeviceManager * deviceManager;
        VkCommandPool commandPool;
    public:
        BufferManager(){};
        BufferManager(LogicDeviceManager * devManager,VkPhysicalDevice physicalDev,VkCommandPool cmdPool){
            device = devManager->getDevice();
            physicalDevice = physicalDev;
            deviceManager = devManager;
            commandPool = cmdPool;
        }
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        VkDevice * getAssignedDevice(){
            return device;
        };

        VkPhysicalDevice getPhysicalDevice(){
            return physicalDevice;
        }
    };
}


#endif //ROCKETSIMULATOR_BUFFERMANAGER_H
