#include "commonLibs.h"
#include "Device/DeviceManager.h"
#include "Device/LogicDeviceManager.h"
#include "Presentation/WindowsSurface.h"
#include "Drawing/CommandBuffer.h"
#include "Drawing/FrameBuffer.h"
#include "Presentation/SwapChain.h"
#include "GraphicPipeline/GraphicPipeline.h"
#include "Drawing/Renderer.h"
namespace Engine{
    class App {
    private:
        int width;
        int height;
        std::string name;
        GLFWwindow* window;
        VkInstance instance;
        DeviceManager devicesManager;
        LogicDeviceManager logicDeviceManager;
        WindowsSurface windowsSurface;
        FrameBuffer frameBuffer;
        CommandBuffer commandBuffer;
        SwapChain swapChain;
        GraphicPipeline graphicPipeline;
        Renderer renderer;
    public:
        App(){}

        App(int w,int h,std::string win_name)
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
        GLFWwindow* getWindow();
    public:
        void run();
        void loop();
    };


}