

#include "WindowsSurface.h"

namespace Engine{
    WindowsSurface::WindowsSurface(){

    }

    void WindowsSurface::createSurface(VkInstance instance,GLFWwindow* window){
        if (glfwCreateWindowSurface(instance,window, nullptr,&surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void WindowsSurface::clean(VkInstance instance) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }

    VkSurfaceKHR WindowsSurface::getSurface() {
        return surface;
    }
}
