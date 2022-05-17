//
// Created by nicomane on 16/05/22.
//

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "../Device/LogicDeviceManager.h"
#include "../Drawing/CommandBuffer.h"
#include "../Presentation/SwapChain.h"
#include "../commonLibs.h"
namespace Engine{
    class Renderer {

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        LogicDeviceManager *logicDeviceManager;
        SwapChain * swapChainCopy;
        CommandBuffer * commandBufferCopy;
        GraphicPipeline* graphicPipelineCopy;
    public:
        Renderer(){};
        Renderer(LogicDeviceManager * logicDevice,CommandBuffer * cb,SwapChain * sc,GraphicPipeline* g){
            logicDeviceManager = logicDevice;
            swapChainCopy = sc;
            commandBufferCopy = cb;
            graphicPipelineCopy = g;
        };

        void createSyncObjects();

        void drawFrame();
        void close();

    };
}



#endif //ENGINE_RENDERER_H
