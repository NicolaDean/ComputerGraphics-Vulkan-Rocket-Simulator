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
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    struct GlobalUniformBufferObject {
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };
}
#endif //ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
