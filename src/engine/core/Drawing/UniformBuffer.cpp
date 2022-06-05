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

    void UniformBuffer::createUniformBuffers() {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);
        uniformBuffers.resize(Constants::IMAGE_COUNT);
        uniformBuffersMemory.resize(Constants::IMAGE_COUNT);

        for (size_t i = 0; i < uniformBuffers.size(); i++) {
            bufferManager.createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }


    void UniformBuffer::updateUniformBuffer(uint32_t currentImage,VkExtent2D swapChainExtent) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::mat4(1.0f);
        //ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ubo.view = Camera::currentCam->viewMatrix;
        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;

        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }
}