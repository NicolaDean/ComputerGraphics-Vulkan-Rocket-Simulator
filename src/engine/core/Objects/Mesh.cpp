//
// Created by nicomane on 02/06/22.
//

#include "Mesh.h"

namespace Engine{

    std::vector<Mesh*>* Mesh::meshes = new std::vector<Mesh*>();

    void Mesh::init() {
        createVertexBuffer();
        createIndexBuffer();
    }

    void Mesh::close() {
        uniformBufferManager.clean();
        vkDestroyBuffer(*bufferManager.getAssignedDevice(), indexBuffer, nullptr);
        vkFreeMemory(*bufferManager.getAssignedDevice(), indexBufferMemory, nullptr);
        vkDestroyBuffer(*bufferManager.getAssignedDevice(), vertexBuffer, nullptr);
        vkFreeMemory(*bufferManager.getAssignedDevice(), vertexBufferMemory, nullptr);
    }

    void Mesh::updateUniformBuffer(uint32_t currentImage) {

        if(notCalculate){
            this->uniformBufferManager.update(currentImage,Camera::currentCam->getPerspectiveMatric() * Camera::currentCam->getCamPosTranslate());
        }else{
            this->uniformBufferManager.update(currentImage,getModelMatrix());//TODO remove swapChainExtent From updateUniform buffer
        }

    }

    void Mesh::updateUniformBufferAbsolutePos(uint32_t currentImage) {
        this->uniformBufferManager.updateAbsolute(currentImage,getModelMatrix());//TODO remove swapChainExtent From updateUniform buffer
    }

    void Mesh::createIndexBuffer() {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        bufferManager.createBuffer(bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         indexBuffer, indexBufferMemory);

        void* data;
        vkMapMemory(*bufferManager.getAssignedDevice(), indexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t) bufferSize);
        vkUnmapMemory(*bufferManager.getAssignedDevice(), indexBufferMemory);
    }

    void Mesh::createVertexBuffer() {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        bufferManager.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         vertexBuffer, vertexBufferMemory);

        void* data;
        vkMapMemory(*bufferManager.getAssignedDevice(), vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t) bufferSize);
        vkUnmapMemory(*bufferManager.getAssignedDevice(), vertexBufferMemory);
    }

    void Mesh::initDescriptor(DescriptorManager *descriptorManager) {
        descriptorManager->pushElementDescriptor({0, UNIFORM, sizeof(UniformBufferObject), nullptr});
        descriptorSets = descriptorManager->createAndGetDescriptorSets(&uniformBufferManager);
    }

}
