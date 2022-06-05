//
// Created by nicomane on 02/06/22.
//

#include "DescriptorManager.h"


namespace Engine{
    void DescriptorManager::createDescriptorSetLayouts(){

        std::vector<VkDescriptorSetLayoutBinding> bindings;
        bindings.resize(bindingsDescriptors.size());
        //This correspond to create the uboLayoutBinding and samplerLayoutBinding..
        for(int i = 0; i < bindingsDescriptors.size(); i++) {
            bindings[i].binding = bindingsDescriptors[i].binding;
            bindings[i].descriptorType = bindingsDescriptors[i].type;
            bindings[i].descriptorCount = 1;
            bindings[i].stageFlags = bindingsDescriptors[i].flags;
            bindings[i].pImmutableSamplers = nullptr;
        }

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());;
        layoutInfo.pBindings = bindings.data();

        if (vkCreateDescriptorSetLayout(*device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }

    }
    void DescriptorManager::createDescriptorSets() {
        // Create uniform buffer
        for (int j = 0; j < elementsDescriptors.size(); j++) {
            if(elementsDescriptors[j].type == UNIFORM) {
                uniformBufferManager.pushUniformBuffer(j);
            }
        }

        // Create Descriptor set
        std::vector <VkDescriptorSetLayout> layouts(Constants::IMAGE_COUNT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(Constants::IMAGE_COUNT);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(Constants::IMAGE_COUNT);

        if (vkAllocateDescriptorSets(*device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        for (size_t i = 0; i < Constants::IMAGE_COUNT; i++) {
            std::vector<VkWriteDescriptorSet> descriptorWrites(elementsDescriptors.size());
            VkDescriptorBufferInfo bufferInfo{};
            VkDescriptorImageInfo imageInfo{};
            int uniformCount = 0;//Used to map ONLY UNIFORM BUFFER
            for (int j = 0; j < elementsDescriptors.size(); j++) {
                if(elementsDescriptors[j].type == UNIFORM) {
                    bufferInfo.buffer = uniformBufferManager.getBuffer(uniformCount,i);
                    uniformCount++;
                    bufferInfo.offset = 0;
                    bufferInfo.range = elementsDescriptors[j].size;
                    descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[j].dstSet = descriptorSets[i];
                    descriptorWrites[j].dstBinding = elementsDescriptors[j].binding;
                    descriptorWrites[j].dstArrayElement = 0;
                    descriptorWrites[j].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    descriptorWrites[j].descriptorCount = 1;
                    descriptorWrites[j].pBufferInfo = &bufferInfo;

                } else if(elementsDescriptors[j].type == TEXTURE) {

                    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                    imageInfo.imageView = elementsDescriptors[j].tex->getImageView();
                    imageInfo.sampler = elementsDescriptors[j].tex->getSampler();

                    descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[j].dstSet = descriptorSets[i];
                    descriptorWrites[j].dstBinding = elementsDescriptors[j].binding;
                    descriptorWrites[j].dstArrayElement = 0;
                    descriptorWrites[j].descriptorType =VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    descriptorWrites[j].descriptorCount = 1;
                    descriptorWrites[j].pImageInfo = &imageInfo;
                }
            }
            vkUpdateDescriptorSets(*bufferManager.getAssignedDevice(),
                                   static_cast<uint32_t>(descriptorWrites.size()),
                                   descriptorWrites.data(), 0, nullptr);
        }

    }

    void DescriptorManager::createDescriptorPool() {
        std::array<VkDescriptorPoolSize, 2> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(Constants::IMAGE_COUNT);
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(Constants::IMAGE_COUNT);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(Constants::IMAGE_COUNT);

        if (vkCreateDescriptorPool(*device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }
}