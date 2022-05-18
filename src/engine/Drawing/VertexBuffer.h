//
// Created by nicomane on 18/05/22.
//

#ifndef ROCKETSIMULATOR_VERTEXBUFFER_H
#define ROCKETSIMULATOR_VERTEXBUFFER_H

#include "../commonLibs.h"
#include "../Vertex/Vertex.h"

namespace Engine{
    class VertexBuffer {
    private:
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkDevice * device;
        VkPhysicalDevice * physicalDevice;
        std::vector<Vertex> vertices;

    public:
        VertexBuffer(){};
        VertexBuffer(VkDevice * dev,VkPhysicalDevice physicalDev){
            device = dev;
            physicalDevice = &physicalDev;
            vertices = {
                    {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
                    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
                    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
            };
        };

        void createVertexBuffer();
        uint32_t  findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void close();

        VkBuffer getVertexBuffer(){
            return vertexBuffer;
        }

        std::vector<Vertex> getVertices(){
            return vertices;
        }

    };
}



#endif //ROCKETSIMULATOR_VERTEXBUFFER_H
