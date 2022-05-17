#include "DeviceManager.h"
#include "../Presentation/SwapChain.h"

namespace Engine{

    DeviceManager::DeviceManager(VkInstance * inst){
        instance = inst;
    }

    void DeviceManager::pickPhysicalDevice(VkSurfaceKHR surface) {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        devices.resize(deviceCount);
        vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device,surface)) {
                physicalDevice = device; //Select device

                printAllDeviceInfo(physicalDevice);
                break;
            }
        }


        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

    }

    void DeviceManager::candidateSelection(){
        //TODO candidate Selection

        // eg give a score to each devie
    }

    void DeviceManager::getDeviceNames() { //TODO print a list of all devices

    }

    VkPhysicalDevice DeviceManager::getSelectedDevice() {
        return physicalDevice;
    }

    void DeviceManager::selectDeviceByName(char *deviceName) { //TODO select a specific device

    }

    bool DeviceManager::isDeviceSuitable(VkPhysicalDevice device,VkSurfaceKHR surface) {

        //Query For Family Indices of our device
        QueueFamilyIndices indices = findQueueFamilies(device,surface);

        //print the device name we are checking
        //DeviceManager::printDeviceName(device);

        //Check For Extensions Support
        bool extensionsSupported = checkDeviceExtensionSupport(device);

        //Check For SwapChain Support with device and compatibility with surface
        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device,surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        //Return true if device has all necessary requirements
        return indices.isComplete() && extensionsSupported && swapChainAdequate;;

    }

    bool DeviceManager::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    void printDeviceName(VkPhysicalDevice device){
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        std::cout << "\tDevice Name: " << deviceProperties.deviceName << "\n";

    }
    void DeviceManager::printAllDeviceInfo(VkPhysicalDevice device){

        std::cout << "----------------------------------------"<<"\n";
        std::cout << "-------------PRINT DEVICE INFO----------"<<"\n";
        std::cout << "----------------------------------------"<<"\n";

        //PRINT ALL DEVICE PROPRIETIES
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        std::cout << "\tAPI version: 0x" << std::hex << deviceProperties.apiVersion << "\n";
        std::cout << "\tDriver version: 0x" << std::hex << deviceProperties.driverVersion << "\n";
        std::cout << "\tVendor ID: 0x" << std::hex << deviceProperties.vendorID << "\n";
        std::cout << "\tDevice ID: 0x" << std::hex << deviceProperties.deviceID << "\n";
        std::cout << "\tPhysical Device Type: " << deviceProperties.deviceType << "\t";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU )
            std::cout << " (Discrete GPU)\n";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU )
            std::cout << " (Integrated GPU)\n";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU )
            std::cout << " (Virtual GPU)\n";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU )
            std::cout << " (CPU)\n";
        std::cout << "\tDevice Name: " << deviceProperties.deviceName << "\n";


        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        std::cout << "\n\tPhysical Device Features:\n";
        std::cout << "\t\tgeometryShader = " << deviceFeatures.geometryShader << "\n";
        std::cout << "\t\ttessellationShader = " << deviceFeatures.tessellationShader << "\n";
        std::cout << "\t\tmultiDrawIndirect = " << deviceFeatures.multiDrawIndirect << "\n";
        std::cout << "\t\twideLines = " << deviceFeatures.wideLines << "\n";
        std::cout << "\t\tlargePoints = " << deviceFeatures.largePoints << "\n";
        std::cout << "\t\tmultiViewport = " << deviceFeatures.multiViewport << "\n";
        std::cout << "\t\tocclusionQueryPrecise = " << deviceFeatures.occlusionQueryPrecise << "\n";
        std::cout << "\t\tshaderFloat64 = " << deviceFeatures.shaderFloat64 << "\n";
        std::cout << "\t\tshaderInt64 = " << deviceFeatures.shaderInt64 << "\n";
        std::cout << "\t\tshaderInt16 = " << deviceFeatures.shaderInt16 << "\n";


        //MEMORY INFO:

        VkPhysicalDeviceMemoryProperties vpdmp;
        vkGetPhysicalDeviceMemoryProperties(device, &vpdmp);
        std::cout << "\n\tMemory Types: " << vpdmp.memoryTypeCount << "\n";

        //MemoryType
        for(unsigned int i = 0; i < vpdmp.memoryTypeCount; i++) {
            VkMemoryType vmt = vpdmp.memoryTypes[i];
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) != 0 )
                std::cout << " DeviceLocal";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0 )
                std::cout << " HostVisible";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) != 0 )
                std::cout << " HostCoherent";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) != 0 )
                std::cout << " HostCached";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) != 0 )
                std::cout << " LazilyAllocated";
            std::cout << "\n";
        }
        //Heap
        for(unsigned int i = 0; i < vpdmp.memoryHeapCount; i++ ) {
            VkMemoryHeap vmh = vpdmp.memoryHeaps[i];
            std::cout << " size = " << std::hex << (unsigned long int)vmh.size;
            if((vmh.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) != 0)
                std::cout << " DeviceLocal";
            std::cout << "\n";
        }

    }


}