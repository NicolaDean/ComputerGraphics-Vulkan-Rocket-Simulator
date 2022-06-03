
#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#include "../Utils/Constants.h"
#include "../Device/LogicDeviceManager.h"
#include "CommandBuffer.h"
#include "../Presentation/SwapChain.h"
#include "../../commonLibs.h"
#include "../Utils/Constants.h"
#include "../DrawingNew/CommandManager.h"

namespace Engine{
    class Core;
    class Renderer {

        int currentFrame = 0;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        LogicDeviceManager *logicDeviceManager;
        SwapChain * swapChainCopy;
        CommandManager * manager;
        GraphicPipeline* graphicPipelineCopy;

    public:
        Renderer(){};
        Renderer(LogicDeviceManager * logicDevice,CommandManager * cb,SwapChain * sc,GraphicPipeline* g){
            logicDeviceManager = logicDevice;
            swapChainCopy = sc;
            manager = cb;
            graphicPipelineCopy = g;
        };

        void createSyncObjects();

        void drawFrame(Core* app);
        void close();

    };
}



#endif //ENGINE_RENDERER_H