//
// Created by nicomane on 30/05/22.
//

#ifndef ROCKETSIMULATOR_BUFFERMANAGER_H
#define ROCKETSIMULATOR_BUFFERMANAGER_H
#include "../commonLibs.h"
namespace Engine{
    class BufferManager {

        VkDevice * device;
        VkPhysicalDevice physicalDevice;

    public:
        BufferManager(){};
        BufferManager(VkDevice * dev,VkPhysicalDevice physicalDev){
            device = dev;
            physicalDevice = physicalDev;
        }
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    };
}


#endif //ROCKETSIMULATOR_BUFFERMANAGER_H
