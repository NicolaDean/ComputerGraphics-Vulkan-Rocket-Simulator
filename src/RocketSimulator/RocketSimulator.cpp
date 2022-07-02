#include "RocketSimulator.h"
#include <math.h>

namespace RocketSimulator{

    /***
     * USER CAN LOAD MODELS AND MODIFY CAMERA BEFORE PROGRAM START HERE
     *
     * WE CAN ALSO DEFINE CUSTOM PIPELINES IF WE WANT ONE DIFFERENT FROM THE DEFAULT
     *
     * (models can bind the default descriptor or bind a new one defined here)
     * /REMEMBER TO MODIFY THE NUMBER OF MODELS IN THE CREATE POOL FUNCTION WHEN ADDING MODEL
     */
    void RocketSimulator::customInit() {

        /****************CAMERA SETTINGS*******************************************/
        Camera * cam0 = new Camera(LOOK_IN_DIRECTION,ORTOGONALE);
        cam0->setPosition(glm::vec3(1,1,1));
        Camera::addCamera(cam0); //CAM 0
       // Camera::currentCam->setPosition({1,1,-1});
       // Camera::currentCam->setAngle({0.1,0,0});
        Camera::currentCam->setNearPlane(0.1);
        Camera::currentCam->setFarPlane(300.0);

        Camera * cam1 = new Camera(LOOK_IN_DIRECTION,ORTOGONALE);
        cam1->setPosition(glm::vec3(0,20,0));
        cam1->setAngle(glm::vec3(-M_PI_2,0,0));

        Camera::addCamera(cam1); //CAM 1

        Camera * cam2 = new Camera(LOOK_IN_DIRECTION,ORTOGONALE);
        Camera::addCamera(cam2); //CAM 1

        Camera::switchCamera(1); //SET CAM 0 as current Cam
        /****************CUSTOM DESCRIPTOR LAYOUTS*********************************/

        //Descriptor For Terrain: (Only Uniform Buffer, No Texture)
        DescriptorManager* terrainDescriptor = descriptorFactory();
        terrainDescriptor->pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT});
        terrainDescriptor->createDescriptorSetLayouts();

        /****************CUSTOM PIPELINES******************************************/
        std::cout<<"Creating new Terrain Pipeline\n";
       GraphicPipelineCustom* terrainPipeline = pipelineFactory("./src/Shaders/compiledShaders/vertNoTexture.spv",
                                                   "./src/Shaders/compiledShaders/fragNoTexture.spv",
                                                   {globalDescriptor,terrainDescriptor});
       GraphicPipelineCustom* skyboxPipeline = pipelineFactory("./src/Shaders/compiledShaders/vertSkybox.spv",
                                                                 "./src/Shaders/compiledShaders/fragSkybox.spv",
                                                                 {globalDescriptor,&descManager});

       /****************LOAD ALL MODELS OF THE APP**********************************/
       float mapSize = 50;
        //PLANE (Size should be half the resolution for nice effect)
        Map * map = new Map(mapSize,2*mapSize,2*mapSize,bufferManager);
        map->init();
        map->initDescriptor(terrainDescriptor);
        map->bindPipeline(terrainPipeline);
        map->setPos(glm::vec3(-(mapSize/2),0,-(mapSize/2)));
        map->populateMapWithRandomObject(&descManager,&graphicPipelineCustom);
        Mesh::meshes->push_back(map);

        //MODEL 2 ROCKET
        Rocket* m2 = new Rocket(bufferManager);
        m2->init();
        m2->bindPipeline(&graphicPipelineCustom);
        m2->initDescriptor(&descManager);
        m2->setPos(glm::vec3(1.0f,1.0f,1.0f));
        m2->setScale(0.05);
        m2->setAngles(glm::vec3(1.0f,0.0f,0.0f));
        Mesh::meshes->push_back(m2);
        this->subscribeMovable(m2);
        m2->trajectory(glm::vec3(5.0f,1.0f,5.0f),3.0f,0.5);

        Skybox* sky =new  Skybox(bufferManager,"./src/Textures/Sky_Night/Night");
        //Skybox* sky = new  Skybox(bufferManager,"./src/Textures/Skybox_Default/Skybox");
        std::cout<<"ADDRESS:" <<sky<<"\n";
        sky->init();
        sky->initDescriptor(&descManager);
        sky->bindPipeline(skyboxPipeline);
        Mesh::meshes->push_back(sky);

        Skybox* sky2 =new  Skybox(bufferManager,"./src/Textures/Skybox_Default/Skybox");
        sky2->init();
        sky2->initDescriptor(&descManager);
        sky2->bindPipeline(skyboxPipeline);

        Skybox* sky3 =new  Skybox(bufferManager,"./src/Textures/Skybox_Tramonto/Tramonto");
        sky3->init();
        sky3->initDescriptor(&descManager);
        sky3->bindPipeline(skyboxPipeline);

        Skybox::rotateSky(); //WORK!!!
        //TODO ADD A METHOD TO CLEANUP SKYBOX NOT IN THE MESH VECTOR
        //BEFORE PASSING A FUNCTION TO BUTTON NEED TO BIND THE FUNCTION TYPE (eg Rocket::launch) and OBJECT POINTER (eg m2)
        auto onLaunchClick = std::bind(&Rocket::launch, m2); //Bind method launch of Rocket to actual object m2
        auto onSkyClick = std::bind(&RocketSimulator::rotateSky, this); //Bind method launch of Rocket to actual object m2
        //auto onCameraClick = std::bind(&Camera::change, m2); //Bind method launch of Rocket to actual object m2

        //TODO ADD A "ANTI DEBOUNCE" SYSTEM FOR BUTTONS (NOW A SINGLE CLICK IS LIKE 10 or more clicks...)
        UImanager::addButton("./src/Textures/UI/launch.png", onLaunchClick,-0.9f,0.9f,0.2f,0.2f);
        UImanager::addButton("./src/Textures/UI/moon.png", onSkyClick,-0.7f,0.9f,0.2f,0.2f);
        UImanager::addButton("./src/Textures/UI/target.png", onLaunchClick,-0.5f,0.9f,0.2f,0.2f);

    }

    void RocketSimulator::rotateSky() {
        std::cout<<"CHANGE SKYBOX ROTATION\n";
        Skybox::rotateSky();
    }

}