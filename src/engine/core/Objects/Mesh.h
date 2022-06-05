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



        //Vertex Buffer
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        //Index Buffer
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        //BufferManager
        BufferManager bufferManager;
        DescriptorManager * descriptorManager;
    protected:
        //Vetices and Indexes
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    public:
        static std::vector<Mesh>* meshes;

        Mesh(){}

        Mesh(BufferManager buffManager){
            bufferManager = buffManager;
        }

        void init();
        void createVertexBuffer();
        void createIndexBuffer();
        void close();


        void bindDescriptor(DescriptorManager *  desc){
            descriptorManager = desc;
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

        DescriptorManager * getDescriptorManager(){
            return descriptorManager;
        }
    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
