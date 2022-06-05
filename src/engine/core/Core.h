#ifndef ROCKETSIMULATOR_APP_H
#define ROCKETSIMULATOR_APP_H
#pragma once
#include "../commonLibs.h"
#include "Device/DeviceManager.h"
#include "Device/LogicDeviceManager.h"
#include "Presentation/WindowsSurface.h"
#include "Drawing/CommandBuffer.h"
#include "Drawing/FrameBuffer.h"
#include "Drawing/Renderer.h"
#include "Drawing/VertexBuffer.h"
#include "Drawing/BufferManager.h"
#include "Drawing/TextureManager.h"
#include "Drawing/DepthImage.h"
#include "Presentation/SwapChain.h"
#include "GraphicPipeline/GraphicPipeline.h"
#include "Utils/ValidationLayer.h"
#include "Objects/Mesh.h"
#include "Objects/Model.h"
#include "Objects/Texture.h"

//NEW

#include "DrawingNew/CommandManager.h"
#include "DrawingNew/DescriptorManager.h"
#include "DrawingNew/GraphicPipelineCustom.h"

#include <memory>
namespace Engine{
    class Core {
    private:
        int width;
        int height;
        bool framebufferResized = false;

        std::string name;
        GLFWwindow* window;
        VkInstance instance;
        DeviceManager devicesManager;
        LogicDeviceManager logicDeviceManager;
        WindowsSurface windowsSurface;
        CommandBuffer commandBuffer;
        FrameBuffer frameBuffer;
        VertexBuffer vertexBuffer;
        TextureManager textureManager;
        DepthImage depthImage;

        GraphicPipeline graphicPipeline;
        Renderer renderer;
    protected:
        BufferManager bufferManager;
        GraphicPipelineCustom graphicPipelineCustom;
        SwapChain swapChain;
        //NEW
        CommandManager manager;
        Model model;
        Texture texture;
        DescriptorManager descManager;

    public:
        Core(){}

        Core(int w,int h,std::string win_name)
        {
            width = w;
            height = h;
            name = win_name;
        }
    private:
        void init();
        void initVulkan();
        void initWindow();

        void main();
        void appLoop();
        void close();
        void createInstance();
        void printExtensionNames();
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        /**
          * Cleen the swap chain before recreation
          */
        void cleanupSwapChain();

        GLFWwindow* getWindow();
    public:
        void customInit();
        void run();
        void loop();
        /**
        * Recreate the swapchain, called if old swap chain is no more usefull (eg window resize)
        */
        void recreateSwapChain();
        void resetResizeFlag(){
            framebufferResized = false;
        }
        bool getResizeFlag() {
            return framebufferResized;
        }


        //FACTORY:

    };


}

#endif //ROCKETSIMULATOR_APP_H
