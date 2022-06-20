#ifndef ROCKETSIMULATOR_VERTEX_H
#define ROCKETSIMULATOR_VERTEX_H

#include <glm/glm.hpp>
#include "../../commonLibs.h"
namespace Engine{
    /**
     * Vertex Format
     *  float: VK_FORMAT_R32_SFLOAT
        vec2: VK_FORMAT_R32G32_SFLOAT
        vec3: VK_FORMAT_R32G32B32_SFLOAT
        vec4: VK_FORMAT_R32G32B32A32_SFLOAT
     */
    //THIS WILL BE USER AS STRUCTURE FOR SHADER
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 norm;
        glm::vec2 texCoord;

        static Vertex vertexFactory(float x,float y,float z,float nx,float ny,float nz,float u,float v){
            Vertex vertex;

            vertex.pos = glm::vec3 (x,y,z);
            vertex.norm = glm::vec3(nx,ny,nz);
            vertex.texCoord = glm::vec2(u,v);

            return vertex;
        }

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, norm);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }
    };
}

#endif //ROCKETSIMULATOR_VERTEX_H
