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

    /***
     * UPDATE THE GLOBAL UNIFORM BUFFER #GLOBAL UNIFORM BUFFER
     * @param currentImage
     */
    void UniformBuffer::updateGlobalUniformBuffer(uint32_t currentImage) {
        GlobalUniformBufferObject gubo{};
        /**********VIEW and Projection************/
        gubo.view = Camera::currentCam->getViewMatrix();//TODO app Camera::perspective and camera customizzation
        gubo.proj = Camera::currentCam->getPerspectiveMatric();
        /********Cam Position**************/
        gubo.eyePos = Camera::currentCam->CamPos;

        /********Setup Ambient light********/
        gubo.lightColor = Light::ambient.lightColor;
        gubo.lightDir   = Light::ambient.lightDir;

        /******Setup Point Lights*********/
        gubo.numLights  = Light::numOfLights;
        for(int i=0;i<Light::sceneLights.size();i++){
            gubo.lights[i] = LightUniform{};
            gubo.lights[i].color = Light::sceneLights.at(i)->color;
            gubo.lights[i].pos   = Light::sceneLights.at(i)->getPos();
        }

        //Copy Buffer into memory
        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(gubo), 0, &data);
        memcpy(data, &gubo, sizeof(gubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }

    /***
     * Update the uniform buffer containing model matrix
     * @param currentImage
     * @param modelMatrix
     */
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
        //TODO MERGE THIS METHOD WITH THE ONE FOR MODELS (no more differences)
        void* data;
        vkMapMemory(*device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*device, uniformBuffersMemory[currentImage]);
    }

    void UniformBuffer::copyBufferToMemory(uint32_t currentImage){
        //TODO CREATE A UNIFIED FUNCTION TO SAVE BUFFER TO MEMROY
    }
}