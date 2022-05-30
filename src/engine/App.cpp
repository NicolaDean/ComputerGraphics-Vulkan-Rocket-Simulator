#include "App.h"



namespace Engine{
    void App::run(){
        init();
        initVulkan();
        main();
        close();
    }

    GLFWwindow* App::getWindow(){
        return window;
    }

    void App::init(){

        //Open GLFW window
        initWindow();
        //Initialize some of the Engine Components
        devicesManager = DeviceManager(&instance);
        swapChain = SwapChain();
        frameBuffer = FrameBuffer();
    }

    void App::initWindow(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); ->now is resizable



        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, App::framebufferResizeCallback);
    }

    void App::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    void App::initVulkan(){
        //CREATE INSTANCE
        createInstance();
        DEBUG::validationLayer.setInstance(&instance);
        DEBUG::validationLayer.setupDebugMessenger();


        printExtensionNames();
        //Create Presentation Layer
        windowsSurface.createSurface(instance,window);
        //QUERY FOR AVAILABLE DEVICES AND SELECT THE BEST ONE
        devicesManager.pickPhysicalDevice(windowsSurface.getSurface());
        //GENERATE A LOGIC DEVICE INTERFACE OF THE SELECTED DEVICE
        logicDeviceManager.generateLogicDevice(devicesManager.getSelectedDevice(),windowsSurface.getSurface());

        bufferManager = BufferManager(logicDeviceManager.getDevice(),devicesManager.getSelectedDevice());
        //Swap Chain
        swapChain.createSwapChain(devicesManager.getSelectedDevice(),*logicDeviceManager.getDevice(),windowsSurface.getSurface(),window);
        swapChain.createImageView(*logicDeviceManager.getDevice());
        //Descriptor Set Layout
        graphicPipeline = GraphicPipeline(logicDeviceManager.getDevice(),bufferManager);
        graphicPipeline.createDescriptorSetLayout();
        //Graphic Pipeline & Render Pass
        graphicPipeline.createRenderPass(swapChain.getSwapChainImageFormat());
        graphicPipeline.createGraphicPipeline(swapChain.getSwapChainExtent());
        //Create Frame Buffer
        frameBuffer.createFrameBuffer(*logicDeviceManager.getDevice(),swapChain.getSwapChainImageViews(),swapChain.getSwapChainExtent(),graphicPipeline.getRenderPass());
        //Create Command Buffer
        commandBuffer = CommandBuffer(logicDeviceManager.getDevice(),&frameBuffer,&vertexBuffer);
        commandBuffer.init(devicesManager.getSelectedDevice(),windowsSurface.getSurface());
        //Vertex Buffer
        vertexBuffer = VertexBuffer(&logicDeviceManager,devicesManager.getSelectedDevice());
        vertexBuffer.createVertexBuffer(&commandBuffer);
        vertexBuffer.createIndexBuffer(&commandBuffer);
        //Uniform Buffer
        graphicPipeline.createUniformBuffers();
        //Descriptor set and Poll
        graphicPipeline.createDescriptorPool();
        graphicPipeline.createDescriptorSet();

        //Create Renderer (to draw Frames)
        renderer = Renderer(&logicDeviceManager,&commandBuffer,&swapChain,&graphicPipeline);
        renderer.createSyncObjects();
    }

    void App::loop() {
        //USER MUST OVERRIDE THIS FUNCTION
        std::cout<<"Original\n";
    }

    void App::appLoop() {

    }

    void App::main(){
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            renderer.drawFrame(this);
        }

        vkDeviceWaitIdle(*logicDeviceManager.getDevice());
    }


    void App::recreateSwapChain() {
        //Minimization
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }

        //Wait the device to be free to do stuff
        vkDeviceWaitIdle(*logicDeviceManager.getDevice());

        //Clean up the mess of old swap chain
        cleanupSwapChain();
        //Vertex Buffer and Index Buffer
        vertexBuffer.close();
        //Swap Chain
        swapChain.createSwapChain(devicesManager.getSelectedDevice(),*logicDeviceManager.getDevice(),windowsSurface.getSurface(),window);
        swapChain.createImageView(*logicDeviceManager.getDevice());
        //Graphic Pipeline
        graphicPipeline = GraphicPipeline(logicDeviceManager.getDevice(),bufferManager);
        graphicPipeline.createRenderPass(swapChain.getSwapChainImageFormat());
        graphicPipeline.createGraphicPipeline(swapChain.getSwapChainExtent());
        //Create Frame Buffer
        frameBuffer.createFrameBuffer(*logicDeviceManager.getDevice(),swapChain.getSwapChainImageViews(),swapChain.getSwapChainExtent(),graphicPipeline.getRenderPass());
    }
    void App::cleanupSwapChain() {
        //Close Frame Buffer
        frameBuffer.close(*logicDeviceManager.getDevice());
        //Close Graphic Pipeline
        graphicPipeline.close();
        //Close SwapChain and ImageView
        swapChain.close(*logicDeviceManager.getDevice());
    }

    void App::close(){

        DEBUG::validationLayer.clean();

        vertexBuffer.close();
        cleanupSwapChain();
        //Close All Semaphore
        renderer.close();
        //Close Command Pool
        commandBuffer.close();
        //Destroy Device
        logicDeviceManager.clean();
        //Destroy Window surface
        windowsSurface.clean(instance);

        //Free instance
        vkDestroyInstance(instance, nullptr);

        //Destroy Window
        glfwDestroyWindow(window);
        glfwTerminate();

        std::cout << "Resources released correctly!\n\n";

    }


    /**
     * It allow to specify some useful information needed by driver in order to optimize the application
     */
    void App::createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //This next struct is not optional and tells the Vulkan driver which global extensions and validation layers
        // we want to use.
        // Global here means that they apply to the entire program and not a specific device,which will become clear in the next few chapters.

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }


        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

    }

    /**
     * Print names of all available extensions
     */
    void App::printExtensionNames(){
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:\n";

        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

}