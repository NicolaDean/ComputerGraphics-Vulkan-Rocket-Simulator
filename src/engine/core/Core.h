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

        VkInstance instance;
        DeviceManager devicesManager;
        LogicDeviceManager logicDeviceManager;
        WindowsSurface windowsSurface;
        FrameBuffer frameBuffer;
        TextureManager textureManager;
        DepthImage depthImage;
        Renderer renderer;
    protected:
        std::vector<GraphicPipelineCustom*> userPipelines;
        std::vector<DescriptorManager*> userDescriptors;

        static GLFWwindow* window;
        BufferManager bufferManager; //TODO PUT THIS CLASS STATIC SO TO REMOVE ALL ITS PASSAGES
        GraphicPipelineCustom graphicPipelineCustom;
        SwapChain swapChain;
        //NEW
        CommandManager manager;
        DescriptorManager descManager;
        DescriptorManager* globalDescriptor;
    public:
        Core(){}

        Core(int w,int h,std::string win_name)
        {
            width = w;
            height = h;
            name = win_name;
        }

        static GLFWwindow* getWindow(){
            return window;
        };

    private:
        void init();
        void initVulkan();
        void initWindow();

        void main();
        void appLoop();
        void close();
        void cleanMeshes();
        void closeUserPipelines();
        void closeUserDescriptors();
        void recreateUserPipelines();
        void createInstance();
        void printExtensionNames();
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        /**
          * Cleen the swap chain before recreation
          */
        void cleanupSwapChain();

    public:
        /****VULKAN HELEPR METHODS****/
        void run();
        void recreateSwapChain();
        void resetResizeFlag(){
            framebufferResized = false;
        }
        bool getResizeFlag() {
            return framebufferResized;
        }

        /*******USERS METHODS********************/
        virtual void updateScene(uint32_t currentImage)=0;
        virtual void customInit()=0;
        virtual void customClose()=0;
        /******FACTORY METHODS********************/
        GraphicPipelineCustom* pipelineFactory(const std::string& VertShader, const std::string& FragShader,std::vector<DescriptorManager *> D);
        DescriptorManager* descriptorFactory();
        //TODO ADD FACTORY FOR OTHER THINGS, LIKE MODELS

    };


}

#endif //ROCKETSIMULATOR_APP_H
