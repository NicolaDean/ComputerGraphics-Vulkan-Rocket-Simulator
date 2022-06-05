//
// Created by nicomane on 03/06/22.
//

#include "CommandManager.h"
#include "../Device/QueueFamily.h"
#include "../Utils/Constants.h"
namespace Engine{
    void CommandManager::createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice,surface);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(*device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }
    void CommandManager::createCommandBuffers() {
        commandBuffers.resize(Constants::IMAGE_COUNT);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1; //if we have multiple buffers we simply increase this number

        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
        /*
         * VK_COMMAND_BUFFER_LEVEL_PRIMARY   -> Can be submitted to a queue for execution, but cannot be called from other command buffers
         * VK_COMMAND_BUFFER_LEVEL_SECONDARY -> Cannot be submitted directly, but can be called from primary command buffers.
         */

        //Allocate command Buffer

        if (vkAllocateCommandBuffers(*device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }
    }

    void CommandManager::recordCommandBuffers() {
        createCommandBuffers();

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0; // Optional
            beginInfo.pInheritanceInfo = nullptr; // Optional

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) !=
                VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = graphicPipeline->getRenderPass();
            renderPassInfo.framebuffer = frameBuffer->getSwapChainFramebuffers(i);
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = graphicPipeline->getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo,
                                 VK_SUBPASS_CONTENTS_INLINE);

            populateCommandBuffers(i);

            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }

        }
    }

    void CommandManager::populateCommandBuffers(int currentImage) {
        //BIND PIPELINE TO COMMAND BUFFER
        vkCmdBindPipeline(commandBuffers[currentImage], VK_PIPELINE_BIND_POINT_GRAPHICS,
                          graphicPipeline->getGraphicPipeline());

        for (auto &mesh : *Mesh::meshes) // access by reference to avoid copying
        {
            //BIND VERTEX BAFFER
            VkBuffer vertexBuffers[] = {mesh.getVertexBuffer()};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffers[currentImage], 0, 1, vertexBuffers, offsets);
           //BIND INDEX BUFFER
            vkCmdBindIndexBuffer(commandBuffers[currentImage], mesh.getIndexBuffer(), 0,
                                 VK_INDEX_TYPE_UINT32);

            //BIND DESCRIPTOR SET
            //TODO GET DESCRIPTOR FROM MODEL
            std::vector<VkDescriptorSet> descriptorSets = *(mesh.getDescriptorSet());

            vkCmdBindDescriptorSets(commandBuffers[currentImage],
                                    VK_PIPELINE_BIND_POINT_GRAPHICS,
                                    graphicPipeline->getPipelineLayout(), 0, 1, &(descriptorSets[currentImage]),
                                    0, nullptr);


            //DRAW COMMAND
            vkCmdDrawIndexed(commandBuffers[currentImage],
                             static_cast<uint32_t>(mesh.getIndices().size()), 1, 0, 0, 0);
        }
    }
}