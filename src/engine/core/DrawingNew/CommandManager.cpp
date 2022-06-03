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
        commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

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

        std::cout<<"Created Command Buffer, Try Record Command:\n";
        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0; // Optional
            beginInfo.pInheritanceInfo = nullptr; // Optional

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) !=
                VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
            std::cout<<"Render Pass Info:\n";
            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = graphicPipeline->getRenderPass();
            renderPassInfo.framebuffer = frameBuffer->getSwapChainFramebuffers(i);
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = graphicPipeline->getSwapChainExtent();

            std::cout<<"Clear Values:\n";
            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
            clearValues[1].depthStencil = {1.0f, 0};
            std::cout<<"Clear Values:\n";
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            std::cout<<"Begin Render Pass:\n";
            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo,
                                 VK_SUBPASS_CONTENTS_INLINE);

            std::cout<<"vkCmdBeginRenderPass:\n";
            populateCommandBuffers(commandBuffers[i], i);

            std::cout<<"populateCommandBuffers:\n";
            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }

        }
    }

    void CommandManager::populateCommandBuffers(VkCommandBuffer commandBuffer, int currentImage) {

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          graphicPipeline->getGraphicPipeline());

        std::cout<<"Bind Command to Pipeline\n";
        VkBuffer vertexBuffers[] = {M1.getVertexBuffer()};
        // property .vertexBuffer of models, contains the VkBuffer handle to its vertex buffer
        VkDeviceSize offsets[] = {0};
        std::cout<<"Allocate Vertex\n";
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        std::cout<<"Bind Vertex\n";
        // property .indexBuffer of models, contains the VkBuffer handle to its index buffer
        vkCmdBindIndexBuffer(commandBuffer, M1.getIndexBuffer(), 0,
                             VK_INDEX_TYPE_UINT32);
        std::cout<<"Bind Index\n";
        // property .pipelineLayout of a pipeline contains its layout.
        // property .descriptorSets of a descriptor set contains its elements.

        std::vector<VkDescriptorSet> descriptorSets = descriptorManager->getDescriptorSet();
        std::cout<<"Cosa succede?\n";
        vkCmdBindDescriptorSets(commandBuffer,
                                VK_PIPELINE_BIND_POINT_GRAPHICS,
                                graphicPipeline->getPipelineLayout(), 0, 1, &descriptorSets[currentImage],
                                0, nullptr);
        std::cout<<"Bind Descriptor\n";
        // property .indices.size() of models, contains the number of triangles * 3 of the mesh.
        vkCmdDrawIndexed(commandBuffer,
                         static_cast<uint32_t>(M1.getIndices().size()), 1, 0, 0, 0);
        std::cout<<"DRAWWWINGr\n";
    }
}