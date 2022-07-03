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
    void UniformBuffer::createUniformBuffers(int buffSize) {
        VkDeviceSize bufferSize = buffSize; //TODO PUT HERE TYPE
        uniformBuffers.resize(Constants::IMAGE_COUNT);
        uniformBuffersMemory.resize(Constants::IMAGE_COUNT);

        for (size_t i = 0; i < uniformBuffers.size(); i++) {
            bufferManager.createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }

    void UniformBuffer::updateGlobalUniformBuffer(uint32_t currentImage) {
        GlobalUniformBufferObject gubo{};
        gubo.view = Camera::currentCam->getViewMatrix();//TODO app Camera::perspective and camera customizzation
        gubo.proj = Camera::currentCam->getPerspectiveMatric();
        gubo.lightColor = glm::vec4(0.6f,0.6,0.6f,0.5);
        gubo.lightDir = glm::vec3(1,2,1);
        gubo.numLights = 2;
        gubo.eyePos = Camera::currentCam->CamPos;

        for(int i=0;i<Light::sceneLights.size();i++){
            gubo.lights[i] = LightUniform{};
            gubo.lights[i].color = Light::sceneLights.at(i)->color;
            gubo.lights[i].pos   = Light::sceneLights.at(i)->getPos();
        }

       /* gubo.lights[0] = LightUniform{};
        gubo.lights[0].color = Light::sceneLights.at(0)->color;
        gubo.lights[0].pos = glm::vec3(0,0,1);
        gubo.lights[1] = LightUniform{};
        gubo.lights[1].color = glm::vec3(0,0,1);
        gubo.lights[1].pos = glm::vec3(0,0,1);*/

        //std::cout <<"COLOR:" <<gubo.lights[0].color.x<< "," <<gubo.lights[0].color.y<<","<<gubo.lights[0].color.z<<"\n";
        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(gubo), 0, &data);
        memcpy(data, &gubo, sizeof(gubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }
    void UniformBuffer::updateUniformBuffer(uint32_t currentImage,glm::mat4 modelMatrix) {
        UniformBufferObject ubo{};
        ubo.model = modelMatrix;

        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }

    void UniformBuffer::updateUniformBufferAbsolutePos(uint32_t currentImage,glm::mat4 modelMatrix){
        UniformBufferObject ubo{};
        ubo.model = modelMatrix;

        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }

    void UniformBuffer::copyBufferToMemory(uint32_t currentImage){
        //TODO CREATE A UNIFIED FUNCTION TO SAVE BUFFER TO MEMROY
    }
}