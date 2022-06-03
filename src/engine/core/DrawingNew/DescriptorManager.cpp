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
        // uniformBufferManager.resizeVector(elementsDescriptors.size());
        // Create uniform buffer
        uniformBuffers.resize(elementsDescriptors.size());
        uniformBuffersMemory.resize(elementsDescriptors.size());
        //toFree.resize(E.size());

        for (int j = 0; j < elementsDescriptors.size(); j++) {
            uniformBuffers[j].resize(MAX_FRAMES_IN_FLIGHT);
            uniformBuffersMemory[j].resize(MAX_FRAMES_IN_FLIGHT);
            if(elementsDescriptors[j].type == UNIFORM) {
                for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
                    VkDeviceSize bufferSize = elementsDescriptors[j].size;
                    bufferManager.createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                     uniformBuffers[j][i], uniformBuffersMemory[j][i]);
                }
                //toFree[j] = true;
            } else {
                //toFree[j] = false;
            }
        }

        std::vector<UniformBuffer> * tmp = uniformBufferManager.getBuffers();

        // Create Descriptor set
        std::vector <VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);

        if (vkAllocateDescriptorSets(*device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        std::cout<<"DescriotorSet created \n";
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            //std::vector <VkWriteDescriptorSet> descriptorWrites(elementsDescriptors.size());
            std::array<VkWriteDescriptorSet, 2> descriptorWrites{};
            int uniformCount = 0; //I use it to scroll uniformBufferArray
            //for (int j = 0; j < elementsDescriptors.size(); j++) {
               // std::cout<<"Giro numero:(" <<i<<","<<j<<")\n";
                //if (elementsDescriptors[j].type == UNIFORM) {

                    VkDescriptorBufferInfo bufferInfo{};
                    //(uniformBufferManager.getBuffer(uniformCount,i));
                    bufferInfo.buffer = uniformBuffers[0][i];
                    bufferInfo.offset = 0;
                    bufferInfo.range = elementsDescriptors[0].size;

                    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[0].dstSet = descriptorSets[i];
                    descriptorWrites[0].dstBinding = elementsDescriptors[0].binding;
                    descriptorWrites[0].dstArrayElement = 0;
                    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    descriptorWrites[0].descriptorCount = 1;
                    descriptorWrites[0].pBufferInfo = &bufferInfo;

                    //std::cout<<elementsDescriptors[j].binding<<"->"<<elementsDescriptors[j].type<<"->"<<elementsDescriptors[j].size<<"\n";
                    printf("UNIFORM\n");
                    uniformCount++;
                    std::cout<<"COUNT -> " <<uniformCount<<"\n";
                //} else if (elementsDescriptors[j].type == TEXTURE) {
                    VkDescriptorImageInfo imageInfo{};
                    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                    imageInfo.imageView = elementsDescriptors[1].tex->getImageView();
                    imageInfo.sampler = elementsDescriptors[1].tex->getSampler();

                    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[1].dstSet = descriptorSets[i];
                    descriptorWrites[1].dstBinding = elementsDescriptors[1].binding;
                    descriptorWrites[1].dstArrayElement = 0;
                    descriptorWrites[1].descriptorType =
                            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    descriptorWrites[1].descriptorCount = 1;
                    descriptorWrites[1].pImageInfo = &imageInfo;
                    printf("TEXTUREE\n");
               // }

            vkUpdateDescriptorSets(*device,static_cast<uint32_t>(descriptorWrites.size()),descriptorWrites.data(), 0, nullptr);
            std::cout<<"ENDED FRAME "<<i<<"\n";
        }
        //}

    }
   /* void DescriptorManager::createDescriptorSets() {
        // uniformBufferManager.resizeVector(elementsDescriptors.size());
        for (int j = 0; j < elementsDescriptors.size(); j++) {
            if (elementsDescriptors[j].type == UNIFORM) {
                std::cout<<"Create a uniform Buffer: "<<j<<"\n";
                uniformBufferManager.pushUniformBuffer(j);
            }
        }

        std::vector<UniformBuffer> * tmp = uniformBufferManager.getBuffers();

        // Create Descriptor set
        std::vector <VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);

        if (vkAllocateDescriptorSets(*device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        std::cout<<"DescriotorSet created \n";
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            std::vector <VkWriteDescriptorSet> descriptorWrites(elementsDescriptors.size());
            int uniformCount = 0; //I use it to scroll uniformBufferArray
            for (int j = 0; j < elementsDescriptors.size(); j++) {
                std::cout<<"Giro numero:(" <<i<<","<<j<<")\n";
                if (elementsDescriptors[j].type == UNIFORM) {

                    VkDescriptorBufferInfo bufferInfo{};
                    //(uniformBufferManager.getBuffer(uniformCount,i));
                    bufferInfo.buffer = ((tmp->at(uniformCount)).getUniformBufferRef())->at(i);
                    bufferInfo.offset = 0;
                    bufferInfo.range = elementsDescriptors[j].size;

                    descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[j].dstSet = descriptorSets[i];
                    descriptorWrites[j].dstBinding = elementsDescriptors[j].binding;
                    descriptorWrites[j].dstArrayElement = 0;
                    descriptorWrites[j].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    descriptorWrites[j].descriptorCount = 1;
                    descriptorWrites[j].pBufferInfo = &bufferInfo;

                   std::cout<<elementsDescriptors[j].binding<<"->"<<elementsDescriptors[j].type<<"->"<<elementsDescriptors[j].size<<"\n";
                    printf("UNIFORM\n");
                    uniformCount++;
                    std::cout<<"COUNT -> " <<uniformCount<<"\n";
                } else if (elementsDescriptors[j].type == TEXTURE) {
                    VkDescriptorImageInfo imageInfo{};
                    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                    imageInfo.imageView = elementsDescriptors[j].tex->getImageView();
                    imageInfo.sampler = elementsDescriptors[j].tex->getSampler();

                    descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[j].dstSet = descriptorSets[i];
                    descriptorWrites[j].dstBinding = elementsDescriptors[j].binding;
                    descriptorWrites[j].dstArrayElement = 0;
                    descriptorWrites[j].descriptorType =
                            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    descriptorWrites[j].descriptorCount = 1;
                    descriptorWrites[j].pImageInfo = &imageInfo;
                    printf("TEXTUREE\n");
                }
            }
            vkUpdateDescriptorSets(*device,static_cast<uint32_t>(descriptorWrites.size()),descriptorWrites.data(), 0, nullptr);
            std::cout<<"ENDED FRAME "<<i<<"\n";
        }

    }*/

    /*void DescriptorManager::createDescriptorSets() {
        uniformBufferManager.resizeVector(elementsDescriptors.size());
        for (int j = 0; j < elementsDescriptors.size(); j++) {
            if (elementsDescriptors[j].type == UNIFORM) {
                std::cout<<"Create a uniform Buffer\n";
                uniformBufferManager.pushUniformBuffer(j);
            }
        }

        std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
        if (vkAllocateDescriptorSets(*device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
        std::vector<VkBuffer> uniformBuffers = uniformBufferManager.getBuffer(0);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = elementsDescriptors[0].size;

            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = elementsDescriptors[1].tex->getImageView();
            imageInfo.sampler = elementsDescriptors[1].tex->getSampler();

            std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = descriptorSets[i];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = descriptorSets[i];
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = 1;
            descriptorWrites[1].pImageInfo = &imageInfo;

            vkUpdateDescriptorSets(*device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }*/

    void DescriptorManager::createDescriptorPool() {
        std::array<VkDescriptorPoolSize, 2> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

        if (vkCreateDescriptorPool(*device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }
}