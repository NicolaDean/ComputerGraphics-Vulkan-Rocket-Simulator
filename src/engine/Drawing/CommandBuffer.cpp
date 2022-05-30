
#include "CommandBuffer.h"
#include "../Device/QueueFamily.h"
namespace Engine{

    void CommandBuffer::init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        createCommandPool(physicalDevice,surface);
        createCommandBuffer();
    }

    void CommandBuffer::close() {
        vkDestroyCommandPool(*device, commandPool, nullptr);
    }

    void CommandBuffer::createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice,surface);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(*device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void CommandBuffer::createCommandBuffer() {
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



    //TODO NEED TO ADD A FUNCTION TO RECORD A GENERIC DRAW COMMAND

    //push a "draw triangle" command
    void CommandBuffer::recordCommandBuffer(int currFrame,uint32_t imageIndex,SwapChain swapChain,GraphicPipeline graphicPipeline) {

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[currFrame], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = graphicPipeline.getRenderPass();
        renderPassInfo.framebuffer = frameBuffer->getSwapChainFramebuffers(imageIndex);
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[currFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


        std::vector<Vertex> vertices = vertexBuffer->getVertices();
        /*for (Vertex v : vertices) {
            printf("{%f,%f}\n",v.pos.x,v.pos.y);
        }*/

        vkCmdBindPipeline(commandBuffers[currFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicPipeline.getGraphicPipeline());
        VkBuffer vertexBuffers[] = {vertexBuffer->getVertexBuffer()};//TODO here we can merge more Vertex Buffer
        VkDeviceSize offsets[] = {0};
        //vkCmdBindVertexBuffers(commandBuffers[currFrame], 0, 1, vertexBuffers, offsets);
        //vkCmdDraw(commandBuffers[currFrame], static_cast<uint32_t>(vertices.size()), 1, 0, 0);

        vkCmdBindVertexBuffers(commandBuffers[currFrame], 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffers[currFrame],vertexBuffer->getIndexBuffer() , 0, VK_INDEX_TYPE_UINT16);

        std::vector<VkDescriptorSet> descriptorSets = graphicPipeline.getDescriptorSets();
        vkCmdBindDescriptorSets(commandBuffers[currFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicPipeline.getPipelineLayout(), 0, 1, &descriptorSets[currFrame], 0, nullptr);

        vkCmdDrawIndexed(commandBuffers[currFrame], static_cast<uint32_t>(vertexBuffer->getIndices().size()), 1, 0, 0, 0);

        vkCmdEndRenderPass(commandBuffers[currFrame]);

        if (vkEndCommandBuffer(commandBuffers[currFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }


}