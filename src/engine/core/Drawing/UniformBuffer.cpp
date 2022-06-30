//
// Created by nicomane on 30/05/22.
//

#include "UniformBuffer.h"

namespace Engine{

    void UniformBuffer::close(){
        //Clean Uniform Buffer
        for (size_t i = 0; i < uniformBuffers.size(); i++) {
            vkDestroyBuffer(*device, uniformBuffers[i], nullptr);
            vkFreeMemory(*device, uniformBuffersMemory[i], nullptr);
        }
    }

    //TODO, put create GLOBAL UNIFORM (or other type of uniform)
    void UniformBuffer::createUniformBuffers() {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject); //TODO PUT HERE TYPE
        uniformBuffers.resize(Constants::IMAGE_COUNT);
        uniformBuffersMemory.resize(Constants::IMAGE_COUNT);

        for (size_t i = 0; i < uniformBuffers.size(); i++) {
            bufferManager.createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }


    void UniformBuffer::updateUniformBuffer(uint32_t currentImage,glm::mat4 modelMatrix) {
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = modelMatrix;
        ubo.view = Camera::currentCam->getViewMatrix();//TODO app Camera::perspective and camera customizzation
        ubo.proj = Camera::currentCam->getPerspectiveMatric();

        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }

    void UniformBuffer::updateUniformBufferAbsolutePos(uint32_t currentImage,glm::mat4 modelMatrix){
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = modelMatrix;
        ubo.view = Camera::currentCam->getViewMatrix();//TODO app Camera::perspective and camera customizzation

        //ONLY MODEL MATRIX

        //TODO clean up this code

        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }
}