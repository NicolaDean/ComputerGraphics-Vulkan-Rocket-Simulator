//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
#include "../../commonLibs.h"
#include "../Drawing/BufferManager.h"
#include "../Geometry/Vertex.h"
namespace Engine{
    class Mesh {
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
    public:
        Mesh(){}

        Mesh(BufferManager buffManager){
            bufferManager = buffManager;
        }

        void init();
        void createVertexBuffer();
        void createIndexBuffer();
        void close();
    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESH_H
