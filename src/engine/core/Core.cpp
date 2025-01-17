#include "Core.h"



namespace Engine{
    GLFWwindow* Core::window;
    void Core::run(){
        init();
        initVulkan();
        main();
        close();
    }



    void Core::init(){
        //Open GLFW window
        initWindow();
        //Initialize some of the Engine Components
        devicesManager = DeviceManager(&instance);
        swapChain = SwapChain();
        frameBuffer = FrameBuffer();
    }

    void Core::initWindow(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); ->now is resizable

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, Core::framebufferResizeCallback);
    }

    void Core::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<Core*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    void Core::initVulkan(){
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
       //Swap Chain
        swapChain.createSwapChain(devicesManager.getSelectedDevice(),*logicDeviceManager.getDevice(),windowsSurface.getSurface(),window);
        swapChain.createImageViews(*logicDeviceManager.getDevice());
        int x = Constants::IMAGE_COUNT;
        std::cout<<"SWAPCHAIN IMAGE COUNT: "<<x<<"\n";
        //Descriptor Set Layout
        //graphicPipeline = GraphicPipeline(logicDeviceManager.getDevice());
        //graphicPipeline.createDescriptorSetLayout();
        graphicPipelineCustom = GraphicPipelineCustom(logicDeviceManager.getDevice(),&swapChain);
        //Graphic Pipeline & Render Pass
        bufferManager = BufferManager(&logicDeviceManager,devicesManager.getSelectedDevice(), nullptr);
        depthImage = DepthImage(bufferManager);
        //graphicPipeline.createRenderPass(swapChain.getSwapChainImageFormat(),depthImage);
        graphicPipelineCustom.createRenderPass(depthImage);
        //Command Pool
        manager = CommandManager(logicDeviceManager.getDevice());
        manager.createCommandPool(devicesManager.getSelectedDevice(),windowsSurface.getSurface());
        //Depth Resources
        textureManager = TextureManager(bufferManager);
        depthImage = DepthImage(bufferManager);
        depthImage.createDepthResources(swapChain.getSwapChainExtent(),textureManager);
        //Create Frame Buffer
        frameBuffer.createFrameBuffer(*logicDeviceManager.getDevice(),swapChain.getSwapChainImageViews(),swapChain.getSwapChainExtent(),graphicPipelineCustom.getRenderPass(),depthImage.getDepthImageView());
        manager.setFrameBuffer(&frameBuffer);
        //Recreate the Buffer manager with the command pool (to help texture manager)
        bufferManager = BufferManager(&logicDeviceManager,devicesManager.getSelectedDevice(),manager.getCommandPool());
        textureManager = TextureManager(bufferManager);

        //**************CREATE DESCRIPTOR MANAGER*************************************************
        //Create Descriptor Manager and DescriptorPool
        descManager = DescriptorManager(bufferManager,&swapChain);
        descManager.createDescriptorPool(logicDeviceManager.getDevice());

        //Create the App descriptorLayout
        descManager.pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT});
        descManager.pushBindingDescriptor({1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT});

        descManager.createDescriptorSetLayouts();


        //************GLOBAL UNIFORM BUFFER DESCRIPTOR*************************************************
        globalDescriptor = descriptorFactory();
        globalDescriptor->pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS});
        globalDescriptor->createDescriptorSetLayouts();
        globalDescriptor->pushElementDescriptor({0, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr});
        globalDescriptor->createDescriptorSets();
        globalDescriptor->setAsGlobal();
        manager.setGlobalDescriptor(globalDescriptor);


        graphicPipelineCustom.createGraphicPipeline("./src/Shaders/compiledShaders/vertShader.spv",
                                                    "./src/Shaders/compiledShaders/fragShader.spv",
                                                    {globalDescriptor,&descManager});
        GraphicPipelineCustom* UIpipeline = pipelineFactory("./src/Shaders/compiledShaders/vertUIshader.spv",
                                                            "./src/Shaders/compiledShaders/fragUIshader.spv",
                                                            {&descManager});
        manager.setGraphicPipeline(&graphicPipelineCustom);

        //INITIALIZE UI
        UImanager::init(bufferManager,UIpipeline,&descManager);
        //INITIALIZE USER SCENE OBJECT PIPELINE AND DESCRIPTOR
        customInit();

        //RECORD COMMAND BUFFER
        manager.createCommandBuffers();
        manager.recordCommandBuffers();
        //Create Renderer (to draw Frames)
        renderer = Renderer(&logicDeviceManager,&manager,&swapChain);
        renderer.createSyncObjects();
    }


    void Core::appLoop() {

    }

    void Core::main(){
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            renderer.drawFrame(this);
        }
        vkDeviceWaitIdle(*logicDeviceManager.getDevice());
    }



    void Core::recreateSwapChain() {

        //printf("Recreated swapchain");
        //TODO CHECK WHY CRASH NOW
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
        cleanupSwapChain();//TODO ADD RESIZE SWAPCHAIN!!!
        //Swap Chain
        swapChain.createSwapChain(devicesManager.getSelectedDevice(),*logicDeviceManager.getDevice(),windowsSurface.getSurface(),window);
        swapChain.createImageViews(*logicDeviceManager.getDevice());
        //Graphic Pipeline
        recreateUserPipelines();
        //Depth resource
        depthImage.createDepthResources(swapChain.getSwapChainExtent(),textureManager);
        //Create Frame Buffer
        frameBuffer.createFrameBuffer(*logicDeviceManager.getDevice(),swapChain.getSwapChainImageViews(),swapChain.getSwapChainExtent(),graphicPipelineCustom.getRenderPass(),depthImage.getDepthImageView());

    }

    void Core::cleanupSwapChain() {
        depthImage.close();
        //Close Frame Buffer
        frameBuffer.close(*logicDeviceManager.getDevice());
        //Close Graphic Pipelines
        closeUserPipelines();
        //Close SwapChain and ImageView
        swapChain.close(*logicDeviceManager.getDevice());
    }

    void Core::customClose(){

    }

    void Core::cleanMeshes(){

        int i=0;
        for (auto mesh : *Mesh::meshes) // access by reference to avoid copying
        {
            std::cout<<"Closing mesh: "<<i<<"\n";
            mesh->close();
            i++;
        }

        UImanager::close();
    }

    void Core::close(){
        //TODO CHECK THE CLEANUP METHODS, A VK BUFFER IS MISSING...
        cleanupSwapChain();
        manager.close();
        //GlobalUniform Buffer
        DescriptorManager::globalDescriptor->closeGlobalUniformBuffer();
        //LayoutSet and Pool Descriptor
        descManager.closeDescriptorPool();
        descManager.close();
        closeUserDescriptors();
        //Vertex and Index Buffer OF ALL MESHES
        cleanMeshes();
        //CLEAN CUSTO OF USER
        customClose();
        //Close All Semaphore
        renderer.close();
        //Close Command Pool
        //commandBuffer.close();
        //Destroy Device
        logicDeviceManager.clean();
        //Destroy Window surface
        windowsSurface.clean(instance);

        //Validation Layer
        DEBUG::validationLayer.clean();
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
    void Core::createInstance() {
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

    void Core::closeUserPipelines() {
        std::cout<<"CLOSE USER PIPELINES\n";
        for(auto p : GraphicPipelineCustom::userPipelines){
            p->close();
        }
        graphicPipelineCustom.close();
        graphicPipelineCustom.closeRenderPass();
    }

    void Core::recreateUserPipelines() {

        std::cout<<"RECREATE USER PIPELINES\n";
        //Recreate render pass
        graphicPipelineCustom.createRenderPass(depthImage);
        graphicPipelineCustom.recreate(&swapChain);
        std::cout<<"MAIN PIPELINE RECREATED\n";
        //Recreate all the graphics pipelines
        for(auto p : GraphicPipelineCustom::userPipelines){
            p->setRenderPass(graphicPipelineCustom.getRenderPass());
            p->recreate(&swapChain);
        }

        std::cout<<"COMPLETED RECREATION OF USER PIPELINES\n";
    }
    GraphicPipelineCustom* Core::pipelineFactory(const std::string& VertShader, const std::string& FragShader,std::vector<DescriptorManager *> D)
    {
        GraphicPipelineCustom* pipeline = new GraphicPipelineCustom(logicDeviceManager.getDevice(),&swapChain);
        pipeline->setRenderPass(graphicPipelineCustom.getRenderPass());
        pipeline->createGraphicPipeline(VertShader,FragShader,D);
        std::cout<<"CREATING -> "<<VertShader<<"\n";
        GraphicPipelineCustom::userPipelines.push_back(pipeline);

        return pipeline;
    }

    DescriptorManager *Core::descriptorFactory() {
        DescriptorManager *tmp = new DescriptorManager(bufferManager,&swapChain);
        userDescriptors.push_back(tmp);
        return tmp;
    }

    void Core::closeUserDescriptors(){
        for(auto d : userDescriptors){
            d->close();
        }
    }
    /**
     * Print names of all available extensions
     */
    void Core::printExtensionNames(){
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

/*
 *         //graphicPipeline.createGraphicPipeline(swapChain.getSwapChainExtent());
        //Create Command Buffer
        //commandBuffer = CommandBuffer(logicDeviceManager.getDevice(),&frameBuffer,&vertexBuffer);
        //commandBuffer.init(devicesManager.getSelectedDevice(),windowsSurface.getSurface());


 * //CREATE AN HELPER CLASS TO MANAGE BUFFER CREATIONS
 textureManager.createTextureImage("./src/Textures/viking_room.png");
 textureManager.createTextureImageView();
 textureManager.createTextureSampler();
 //Vertex Buffer
 vertexBuffer = VertexBuffer(&logicDeviceManager,devicesManager.getSelectedDevice());
 vertexBuffer.createVertexBuffer(&commandBuffer);
 vertexBuffer.createIndexBuffer(&commandBuffer);
 //Uniform Buffer
 graphicPipeline.createUniformBuffers(bufferManager);
 //Descriptor set and Poll
 graphicPipeline.createDescriptorPool();
 graphicPipeline.createDescriptorSet(textureManager);*/