
#include "Renderer.h"
#include "../Core.h"
#include <chrono>

namespace Engine{

    void Renderer::close() {
        VkDevice device = *logicDeviceManager->getDevice();
        //DeVK_IMAGE_LAYOUT_PRESENT_SRC_KHRstroy Semaphore
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }

    }
    void Renderer::createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(Constants::IMAGE_COUNT, VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        VkDevice device = *logicDeviceManager->getDevice();

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }

    }

    void Renderer::drawFrame(Core* app) {

        // Get starting timepoint
        auto start = std::chrono::high_resolution_clock::now();

        VkDevice device = *logicDeviceManager->getDevice();
        VkSwapchainKHR swapChain = swapChainCopy->getSwapChain();
        std::vector<VkCommandBuffer> commandBuffers = manager->getCommandBuffers();

        vkWaitForFences(device, 1, &inFlightFences[currentFrame],VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        //std::cout<<"ImageIndex->" <<imageIndex<<"\n";
        VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            app->recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        //UPDATE UNIFORM BUFFER

        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(device, 1, &imagesInFlight[imageIndex],
                            VK_TRUE, UINT64_MAX);
        }
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        vkResetCommandBuffer(*manager->getCommandBuffers(imageIndex), /*VkCommandBufferResetFlagBits*/ 0);
        //commandBufferCopy->recordCommandBuffer(currentFrame, imageIndex,*swapChainCopy,*graphicPipelineCopy);
        manager->recordCommandBuffer(imageIndex);

        app->updateScene(imageIndex);
        //manager->updateBufferManager(imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] ={VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = manager->getCommandBuffers(imageIndex);
        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(device, 1, &inFlightFences[currentFrame]);


        if (vkQueueSubmit(logicDeviceManager->getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(logicDeviceManager->getPresentQueue(), &presentInfo);

        //TODO check why in this specific point Validation layer comunicate "suboptimal KHR"
        // it is right, but why it print out before i can recreate swapcahin?
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || app->getResizeFlag()) {
            app->resetResizeFlag(); //put false the resize flag
            app->recreateSwapChain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

        // Get ending timepoint
        auto stop =  std::chrono::high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto duration =  std::chrono::duration_cast< std::chrono::microseconds>(stop - start);

        //TODO CALCULATE FPS!!!
        //std::cout << "Time taken by function: "<< std::dec<<duration.count() << " microseconds\n";
    }
}