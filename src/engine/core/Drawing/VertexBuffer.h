//
// Created by nicomane on 18/05/22.
//

#ifndef ROCKETSIMULATOR_VERTEXBUFFER_H
#define ROCKETSIMULATOR_VERTEXBUFFER_H

#include "../../commonLibs.h"
#include "../Geometry/Vertex.h"
#include "../Geometry/UniformBufferObject.h"
#include "../Device/LogicDeviceManager.h"

//TODO The previous chapter already mentioned that you should allocate multiple resources like buffers from a single memory allocation, but in fact you should go a step further. Driver developers recommend that you also store multiple buffers, like the vertex and index buffer, into a single VkBuffer and use offsets in commands like vkCmdBindVertexBuffers. The advantage is that your data is more cache friendly in that case, because it's closer together. It is even possible to reuse the same chunk of memory for multiple resources if they are not used during the same render operations, provided that their data is refreshed, of course. This is known as aliasing and some Vulkan functions have explicit flags to specify that you want to do this
namespace Engine{
    class CommandBuffer;
    class VertexBuffer {
    private:
        //BUFFERS
        ////VertexBuffer:
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        ////IndexBuffer:
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        //DEVICES POINTERS
        LogicDeviceManager * logicDeviceManager;
        VkPhysicalDevice  physicalDevice;

        //DATA (put into a singleton??)
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;

    public:
        VertexBuffer(){};
        VertexBuffer(LogicDeviceManager * device ,VkPhysicalDevice physicalDev){
            logicDeviceManager = device;
            physicalDevice = physicalDev;
            vertices = {
                    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f},{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
                    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f},{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

                    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f},{1.0f, 1.0f}},
                    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f},{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}
            };
            indices = {
                    0, 1, 2, 2, 3, 0,
                    4, 5, 6, 6, 7, 4
            };
        };

        //DEDICATED BUFFER CREATIONS
        void createVertexBuffer(CommandBuffer * cmdBuffer);
        void createIndexBuffer(CommandBuffer * cmdBuffer);
        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage,VkExtent2D swapChainExtent);
        //BUFFER CREATION HELPERS:
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size,CommandBuffer * cmdBuffer);

        //FIND COMPATIBLE MEMORY TYPE FOR CPU AND GPU
        uint32_t  findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        //CLOSE ALL
        void close();

        //GETTER-------------------------------------------------------------
        VkBuffer getVertexBuffer(){
            return vertexBuffer;
        }

        std::vector<Vertex> getVertices(){
            return vertices;
        }

        std::vector<uint16_t> getIndices(){
            return indices;
        }

        VkBuffer getIndexBuffer(){
            return indexBuffer;
        }
    };
}



#endif //ROCKETSIMULATOR_VERTEXBUFFER_H
