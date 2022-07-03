//
// Created by nicomane on 19/05/22.
//

#ifndef ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
#define ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
#include "../../commonLibs.h"
#include <glm/glm.hpp>

namespace Engine{
    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
    };

    struct LightUniform{
        glm::vec3 pos;
        glm::vec3 color;
    };

    struct GlobalUniformBufferObject {
        glm::mat4 view;
        glm::mat4 proj;
        glm::vec3 lightDir;
        glm::vec4 lightColor;
        glm::vec3 eyePos;
        LightUniform lights[2];
        int numLights;
    };


}
#endif //ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
