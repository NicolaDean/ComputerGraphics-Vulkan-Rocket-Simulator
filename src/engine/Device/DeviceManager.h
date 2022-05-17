#include "../commonLibs.h"
#include "QueueFamily.h"
#include "../Utils/Constants.h"

namespace Engine{
    class DeviceManager {
    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        uint32_t deviceCount = 0;
        VkInstance *instance;
        std::vector<VkPhysicalDevice> devices;

    public:
        /**
         * Constructor
         */
        DeviceManager(VkInstance * inst);
        DeviceManager(){}
        /**
         * Check presence of devices and select the first device compatible with
         * our application
         */
        void pickPhysicalDevice(VkSurfaceKHR surface);

        /**
         * give each device a score and select the best one
         */
        void candidateSelection();

        /**
         * select a specific device chosen by user
         * @param deviceName name of device to select
         */
        void selectDeviceByName(char * deviceName);

        /**
         * get list of devices names
         */
        void getDeviceNames();

        /**
         * check if device is compatible with our app
         * @param device device to check
         * @return
         */
        bool isDeviceSuitable(VkPhysicalDevice device,VkSurfaceKHR surface);

        /**
         * Check if a device is compatible with all required extensions
         * @param device  device to check
         * @return true if all supported
         */
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        /**
         *
         * @return the selected device
         */
        VkPhysicalDevice getSelectedDevice();


        /**
         * check if a specific device support all the required extensions
         * @param device device to check
         * @return true if all extensions are supported
         */
        bool checkDeviceExtensions(VkPhysicalDevice device);

        void printAllDeviceInfo(VkPhysicalDevice device);
    };
}

