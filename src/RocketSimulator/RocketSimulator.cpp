#include "RocketSimulator.h"
#include <math.h>
#include "Models/Platform.h"

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
        /****************POSITIONS SETTINGS*******************************************/

        glm::vec3  startPos=glm::vec3(1.0f,1.0f,1.0f);

        //Set Target (bottom is fake)
        glm::vec3 target= glm::vec3(10.0f,1.0f,10.0f);

        /****************CUSTOM DESCRIPTOR LAYOUTS*********************************/
        //1)GLOBAL UNIFORM BUFFER DESCRIPTOR (IS INSIDE CORE)
        //2)DESCRIPTOR FOR NORMAL 3D MODEL WITH TEXTURE AND UB (IS INSIDE CORE)
        //3) DESCRIPTOR FOR TERRAIN (ONLY 3d MODEL no TEXTURE)
        DescriptorManager* terrainDescriptor = descriptorFactory();
        terrainDescriptor->pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT});
        terrainDescriptor->createDescriptorSetLayouts();
        //4)(END)
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
        float rocketScale=0.06;
        m2->init();
        m2->bindPipeline(&graphicPipelineCustom);
        m2->initDescriptor(&descManager);
        m2->setPos(startPos);
        //cam2-> set track
        m2->setScale(rocketScale);
        m2->setAngles(glm::vec3(0.0f,0.0f,0.0f));
        Mesh::meshes->push_back(m2);
        this->subscribeMovable(m2);
        m2->trajectory(target,8.0f,0.5);

        /****************CAMERA SETTINGS*******************************************/
        Camera * cam0 = new Camera(LOOK_IN_DIRECTION,ORTOGONALE);
        cam0->setPosition(glm::vec3(startPos.x+4,startPos.y+0.5,startPos.z));
        Camera::addCamera(cam0); //CAM 0
        cam0->setAngle(glm::vec3(0,M_PI_2,0));

        // Camera::currentCam->setPosition({1,1,-1});
        // Camera::currentCam->setAngle({0.1,0,0});
        Camera::currentCam->setNearPlane(0.1);
        Camera::currentCam->setFarPlane(300.0);

        Camera * cam1 = new Camera(LOOK_IN_DIRECTION,ORTOGONALE);
        cam1->setPosition(glm::vec3(startPos.x,20,startPos.z));
        cam1->setAngle(glm::vec3(-M_PI_2,0,0));

        Camera::addCamera(cam1); //CAM 1

        //LOOKAT Camera (Follows the rocket)
        Camera * cam2 = new Camera(LOOK_AT_CAMERA,ORTOGONALE);
        cam2->setPosition(glm::vec3(startPos.x+4,startPos.y+0.5,startPos.z));
        cam2->setAngle(glm::vec3(M_PI_4,0,0));
        cam2->setTarget(m2);
        Camera::addCamera(cam2); //
        cam2->switchType(LOOK_AT_CAMERA);


        Camera * cam3 = new Camera(LOOK_IN_DIRECTION,ORTOGONALE);
        cam3->setPosition(glm::vec3(target.x+4,target.y+0.5,target.z));
        Camera::addCamera(cam3); //CAM 0
        cam3->setAngle(glm::vec3(0,M_PI_2,0));


        Camera::switchCamera(0); //SET CAM 0 as current Cam

        /********************SKYBOX CREATION********************************/
        //PLATFORM
        Model* platform = new Model("./src/Models/platform.obj",
              "./src/Textures/platform.jpg",bufferManager);
        //Platform* platform = new Platform(bufferManager);
        platform->init();
        platform->bindPipeline(&graphicPipelineCustom);
        platform->initDescriptor(&descManager);
        platform->setPos(glm::vec3(startPos.x,Map::getMapHeight(startPos.x,startPos.z),startPos.z));
        platform->setScale(rocketScale*11);
        platform->setAngles(glm::vec3(0.0f,0.0f,0.0f));
        Mesh::meshes->push_back(platform);

        //Platform target (movable?)

        Platform* platformTarget = new Platform(bufferManager);
        platformTarget->init();
        platformTarget->bindPipeline(&graphicPipelineCustom);
        platformTarget->initDescriptor(&descManager);
        platformTarget->setPos(glm::vec3(target.x,Map::getMapHeight(target.x,target.z),target.z));
        platformTarget->setScale(rocketScale*11);
        platformTarget->setAngles(glm::vec3(0.0f,0.0f,0.0f));
        Mesh::meshes->push_back(platformTarget);
        this->subscribeMovable(platformTarget);


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

        //TODO ADD A STATIC METHOD TO MODIFY "AMBIENT LIGHT SETTINGS"
        /****************************LIGHT SETUP******************************************/
        //TO ADD LIGHT: insert lightPos (x,y,z) and lightColor (r,g,b,intensity)  20 is a good number for intensity (1 imperceptible 50 super high)
        Light * light1 = new Light(glm::vec3(-5,3,2),glm::vec4(0.0,0,1,20));
        Light * light2 = new Light(glm::vec3(5,3,1),glm::vec4(1,0,0,20));

        /**************************AMBIENT LIGHT SETUP***********************************/
        //W in color is the intensity COLOR:(r,g,b,intensity)
        Light::setAmbientLight(glm::vec3(0,1,1),glm::vec4(0.6f,0.6,0.6f,0.5));

        /****************************UI COMPOSITION***************************************/
        //BEFORE PASSING A FUNCTION TO BUTTON NEED TO BIND THE FUNCTION TYPE (eg Rocket::launch) and OBJECT POINTER (eg m2)
        auto onLaunchClick = std::bind(&Rocket::launch, m2); //Bind method launch of Rocket to actual object m2
        auto onSkyClick = std::bind(&RocketSimulator::rotateSky, this); //Bind method launch of Rocket to actual object m2
        auto onTargetClick = std::bind(&Platform::setTarget, platformTarget); //Bind method target of Rocket to actual object m2
        auto onSwitchClick = std::bind(&RocketSimulator::switchCamera, this); //Bind method launch of Rocket to actual object m2

        //auto onCameraClick = std::bind(&Camera::change, m2); //Bind method launch of Rocket to actual object m2

        //TODO ADD A "ANTI DEBOUNCE" SYSTEM FOR BUTTONS (NOW A SINGLE CLICK IS LIKE 10 or more clicks...)
        UImanager::addButton("./src/Textures/UI/launch.png", onLaunchClick,-0.9f,0.9f,0.2f,0.2f);
        UImanager::addButton("./src/Textures/UI/moon.png", onSkyClick,-0.7f,0.9f,0.2f,0.2f);
        UImanager::addButton("./src/Textures/UI/target.png", onTargetClick,-0.5f,0.9f,0.2f,0.2f);
        UImanager::addButton("./src/Textures/UI/switch.png", onSwitchClick,-0.3f,0.9f,0.2f,0.2f);
    }

    void RocketSimulator::rotateSky() {
        std::cout<<"CHANGE SKYBOX ROTATION\n";
        Skybox::rotateSky();
    }

    void RocketSimulator::changeCameraTarget(){
        std::cout<<"CHANGE TARGET CAM\n";
        Camera::switchCamera(1); //SET CAM 0 as current Cam
        //Platform::enableTarget();

    }

    void RocketSimulator::switchCamera(){
        std::cout<<"SWITCH CAM\n";
        Camera::nextCamera();

    }

}