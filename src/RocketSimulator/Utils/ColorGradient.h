//
// Created by nicomane on 12/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COLORGRADIENT_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COLORGRADIENT_H

#include "../../engine/commonLibs.h"
namespace Engine{
    class ColorGradient {

    public:

        static glm::vec3 getColor(int r,int g,int b);
        static glm::vec3 getColor(glm::vec3 colorA, glm::vec3 colorB,float gradient);
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_COLORGRADIENT_H
