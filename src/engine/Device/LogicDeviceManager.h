#include "../commonLibs.h"
#pragma once
namespace Engine{

    class LogicDeviceManager {

    private:
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

    public:
        LogicDeviceManager(){}

        VkQueue getGraphicsQueue(){
            return graphicsQueue;
        }
        VkQueue getPresentQueue(){
            return presentQueue;
        }
        void generateLogicDevice(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface);
        VkDevice* getDevice();
        void clean();
    };

}
