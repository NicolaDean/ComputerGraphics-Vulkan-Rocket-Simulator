#ifndef ENGINE_CONSTANTS_H
#define ENGINE_CONSTANTS_H

#include "../../commonLibs.h"

#define MAX_FRAMES_IN_FLIGHT 2

namespace Engine{
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    class Constants {

        static int WIDTH;
        static int HEIGHT;
        //static vertex
    };

    class VertexFilesPath{
        //static
    };

}

#endif //ENGINE_CONSTANTS_H

