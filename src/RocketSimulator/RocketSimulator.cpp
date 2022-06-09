#include "RocketSimulator.h"

using namespace Engine;

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
        Camera::setCamera(new Camera(LOOK_IN_DIRECTION,ORTOGONALE));
        Camera::currentCam->setPosition({1,1,2});
        Camera::currentCam->setAngle({0.1,0,0});
        /****************CUSTOM DESCRIPTOR LAYOUTS*********************************/

        //Descriptor For Terrain: (Only Uniform Buffer, No Texture)
        DescriptorManager* terrainDescriptor = descriptorFactory();
        terrainDescriptor->pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT});
        terrainDescriptor->createDescriptorSetLayouts();
        //
        //Descriptor For GlobalUniformBuffer : (Only GlobalUniformBuffer)
        DescriptorManager* globalUniformDescriptor = descriptorFactory();
        globalUniformDescriptor->pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT});

        /****************CUSTOM PIPELINES******************************************/
        std::cout<<"Creating new Terrain Pipeline\n";
       GraphicPipelineCustom* terrainPipeline = pipelineFactory("./src/Shaders/compiledShaders/vertNoTexture.spv",
                                                   "./src/Shaders/compiledShaders/fragNoTexture.spv",
                                                   {terrainDescriptor});
        //GraphicPipelineCustom* skyBoxPipeline = pipelineFactory();
       /****************LOAD ALL MODELS OF THE APP**********************************/
        //MODEL 1:
        Model* m1 = new Model("./src/Models/Desert/cactus01.obj",
                              "./src/Textures/desert.jpeg",bufferManager);
        m1->init();
        m1->setScale(0.08);
        m1->setPos(glm::vec3(0.8f,1.0f,1.0f));
        m1->bindPipeline(&graphicPipelineCustom);
        m1->initDescriptor(&descManager);
        Mesh::meshes->push_back(m1);


        m1 = new Model("./src/Models/Desert/cactus02.obj",
                              "./src/Textures/desert.jpeg",bufferManager);
        m1->init();
        m1->bindPipeline(&graphicPipelineCustom);
        m1->initDescriptor(&descManager);
        m1->setPos(glm::vec3(1.2f,1.0f,1.0f));
        m1->setScale(0.08);
        Mesh::meshes->push_back(m1);

        //MODEL 2:
        Rocket* m2 = new Rocket(bufferManager);
        m2->init();
        m2->bindPipeline(&graphicPipelineCustom);
        m2->initDescriptor(&descManager);

        m2->setPos(glm::vec3(1.0f,1.0f,1.0f));
        m2->setScale(0.03);
        Mesh::meshes->push_back(m2);
        this->subscribeMovable(m2);
        m2->launch();

        //Square test
        /*Square* s1 = new Square(bufferManager);
        s1->init();
        s1->initDescriptor(terrainDescriptor);
        s1->bindPipeline(terrainPipeline);
        Mesh::meshes->push_back(s1);*/
    }
}