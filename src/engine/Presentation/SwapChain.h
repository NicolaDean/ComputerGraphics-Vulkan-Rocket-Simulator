#pragma once
#include "../commonLibs.h"

#include <cstdint> // Necessary for uint32_t
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp

/**
 * Swap chain is the component that will own the buffers we will render to before we visualize them on the screen
 * I summary is like a queue containing the images to be presented on screen
 */
namespace Engine {
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device,VkSurfaceKHR surface);

    /**
     * This class allow to select the best configuration possible for our swap chain
     */
    class SwapChain {
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
    public:
        SwapChain(){

        }

        VkExtent2D getSwapChainExtent(){
            return swapChainExtent;
        }

        VkFormat getSwapChainImageFormat(){
            return swapChainImageFormat;
        }

        std::vector<VkImageView> getSwapChainImageViews(){
            return swapChainImageViews;
        }

        VkSwapchainKHR getSwapChain(){
            return swapChain;
        }
        /**
         * Create the actual swapchain object
         * @param device  device to pair with the swapchain
         * @param surface  surface to pair with swapchain
         */
        void createSwapChain(VkPhysicalDevice physicalDevice,VkDevice device,VkSurfaceKHR surface,GLFWwindow * window);

        void createImageView(VkDevice device);

        void close(VkDevice device);

        /**
         * Chose the
         * @param availableFormats VkSurfaceFormatKHR contains a format and a colorSpace member
         * -format: specifies the color channels and types
         *          eg:VK_FORMAT_B8G8R8A8_SRGB means that we store the B, G, R and alpha with 8bit channel (32bit)
         * -colorSpace: indicates if the SRGB color space is supported or not using the VK_COLOR_SPACE_SRGB_NONLINEAR_KHR flag
         * @return
         */
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        /**
         * Presentation Modes represents the actual conditions for showing images to the screen:
         * 4 Possible Modes:
         * -VK_PRESENT_MODE_IMMEDIATE_KHR
         * -VK_PRESENT_MODE_FIFO_KHR:
         * -VK_PRESENT_MODE_FIFO_RELAXED_KHR:
         * -VK_PRESENT_MODE_MAILBOX_KHR:
         * @param availablePresentModes
         * @return
         */
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);


        /**
         *
         * @param capabilities
         * @return
         */
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,GLFWwindow * window);
    };
}

