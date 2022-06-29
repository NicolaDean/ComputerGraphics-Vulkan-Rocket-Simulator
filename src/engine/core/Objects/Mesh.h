//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
#include "../../commonLibs.h"
#include "../Drawing/BufferManager.h"
#include "../Geometry/Vertex.h"
#include "../DrawingNew/DescriptorManager.h"
#include "Entity.h"
#include "../DrawingNew/GraphicPipelineCustom.h"

namespace Engine{
    class Mesh:public Entity  {
        /*VULKAN BUFFERS AND VARIABLES*/
        //Vertex Buffer
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        //Index Buffer
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        //BufferManager
        BufferManager bufferManager;

    protected:
        /****VERTEX AND INDEX FOR TRIANGLES*****/
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        /******VULKAN COMPONENTS*****************/
        UniformBufferManager uniformBufferManager;
        std::vector<VkDescriptorSet> descriptorSets;
        GraphicPipelineCustom* pipeline;


    public:
        static std::vector<Mesh*>* meshes; //GLOBAL MESH ARRAY


        Mesh(): Entity(){}

        Mesh(BufferManager buffManager): Entity(){
            bufferManager = buffManager;
            uniformBufferManager = UniformBufferManager(buffManager);
        }

        void init();
        void createVertexBuffer();
        void createIndexBuffer();
        void updateUniformBuffer(uint32_t currentImage);
        void updateUniformBufferAbsolutePos(uint32_t currentImage);
        virtual void initDescriptor(DescriptorManager* descriptorManager);
        virtual void update(float dt){}
        virtual void close() = 0;


        /********************GETTER SETTER********************************/

        static void addMesh(Mesh * m){
            meshes->push_back(m);
        }
        UniformBufferManager* getUniformBufferManager(){
            return &uniformBufferManager;
        }
        std::vector<VkDescriptorSet>* getDescriptorSet(){
            return &descriptorSets;
        }

        void setBufferManager(BufferManager bufferMng){
            bufferManager = bufferMng;
        }
        VkBuffer getVertexBuffer(){
            return vertexBuffer;
        }
        VkBuffer getIndexBuffer(){
            return indexBuffer;
        }

        std::vector<Vertex> getVertices(){
            return vertices;
        }
        std::vector<uint32_t> getIndices(){
            return indices;
        }

        GraphicPipelineCustom* getPipeline(){
            return pipeline;
        }
        void bindPipeline(GraphicPipelineCustom* pip){
            pipeline = pip;
        }

    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
