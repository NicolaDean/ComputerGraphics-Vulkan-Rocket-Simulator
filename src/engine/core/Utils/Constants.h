#ifndef ENGINE_CONSTANTS_H
#define ENGINE_CONSTANTS_H

#include "../../commonLibs.h"

#define MAX_FRAMES_IN_FLIGHT 2

namespace Engine{
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    class Constants {
    public:
        static int WIDTH;
        static int HEIGHT;
        static uint32_t IMAGE_COUNT;
        //static VkClearColorValue initialBackgroundColor;
        //static vertex

        static void setImageCount(uint32_t count);
    };

    class App_Singleton{

    };

    class VertexFilesPath{
        //static
    };

}

#endif //ENGINE_CONSTANTS_H

