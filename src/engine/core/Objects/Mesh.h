//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
#include "../../commonLibs.h"
#include "../Drawing/BufferManager.h"
#include "../Geometry/Vertex.h"
#include "../DrawingNew/DescriptorManager.h"

namespace Engine{
    class Mesh  {
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
        //Vetices and Indexes
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        //DESCRIPTOR AND UNIFORM BUFFERS OF MY MODEL
        UniformBufferManager uniformBufferManager;
        std::vector<VkDescriptorSet> descriptorSets;

        //MESH WORLD INFO
        glm::vec3 pos = glm::vec3(1,1,1);
        glm::vec3 orientation = glm::vec3(0,0,1);
        glm::mat4 modelMatrix = glm::mat4(1.0f);

    public:
        static std::vector<Mesh>* meshes;


        Mesh(){}

        Mesh(BufferManager buffManager){
            bufferManager = buffManager;
            uniformBufferManager = UniformBufferManager(buffManager);
        }

        void init();
        void createVertexBuffer();
        void createIndexBuffer();
        void updateUniformBuffer(uint32_t currentImage,glm::mat4 modelMatrix);
        void close();
        /********************MOVEMENT********************************/
        void move(){
            modelMatrix = glm::translate(glm::mat4(1.0f),pos);
        }

        glm::mat4 getModelMatrix(){
            return modelMatrix;
        }

        /********************GETTER SETTER********************************/
        UniformBufferManager* getUniformBufferManager(){
            return &uniformBufferManager;
        }
        std::vector<VkDescriptorSet>* getDescriptorSet(){
            return &descriptorSets;
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

    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
