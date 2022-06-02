//
// Created by nicomane on 19/05/22.
//

#ifndef ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
#define ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
#include "../commonLibs.h"
#include <glm/glm.hpp>

namespace Engine{
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
}
#endif //ROCKETSIMULATOR_UNIFORMBUFFER_STRUCT_H
