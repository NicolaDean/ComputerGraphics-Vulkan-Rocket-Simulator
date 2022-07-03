//
// Created by nicomane on 19/05/22.
//

#ifndef ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
#define ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
#include "../../commonLibs.h"
#include <glm/glm.hpp>

#define LIGHT_NUM 2
namespace Engine{
    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
    };

    struct LightUniform{
        alignas (16)glm::vec3 pos;
        alignas (16)glm::vec4 color;
    };

    struct GlobalUniformBufferObject {
        alignas (16)glm::mat4 view;
        alignas (16)glm::mat4 proj;
        alignas (16)glm::vec3 lightDir;
        alignas (16)glm::vec4 lightColor;
        alignas (16) glm::vec3 eyePos;
        LightUniform lights[LIGHT_NUM];
        alignas (4)int numLights;
    };


}
#endif //ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
