//
// Created by nicomane on 18/05/22.
//
#pragma once
#ifndef ROCKETSIMULATOR_VALIDATIONLAYER_H
#define ROCKETSIMULATOR_VALIDATIONLAYER_H

#include "../commonLibs.h"


#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace Engine{


    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    std::vector<const char*> getRequiredExtensions();
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    bool checkValidationLayerSupport();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);

//DEFINITION OF CLASS VALIDATION LAYER:
    class ValidationLayer{
        VkDebugUtilsMessengerEXT debugMessenger;
        VkInstance * instance;

    public:
        ValidationLayer(){

        }

        void setInstance(VkInstance * instance_copy){
            instance = instance_copy;
        }

        void setupDebugMessenger() {
            if (!enableValidationLayers) return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            if (CreateDebugUtilsMessengerEXT(*instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
                throw std::runtime_error("failed to set up debug messenger!");
            }
        }

        void clean(){
            if (enableValidationLayers) {
                DestroyDebugUtilsMessengerEXT(*instance, debugMessenger, nullptr);
            }
        }

        static ValidationLayer factory(){
            return ValidationLayer();
        }

    };

    //CREATE A SINGLETON OF THE VALIDATION LAYER
    class DEBUG{
    public:
        static int a;
        static ValidationLayer validationLayer;

    };

    //DEBUG::validationLayer = ValidationLayer();

}
#endif //ROCKETSIMULATOR_VALIDATIONLAYER_H
