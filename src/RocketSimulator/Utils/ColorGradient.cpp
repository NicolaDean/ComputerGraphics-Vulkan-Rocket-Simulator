//
// Created by nicomane on 12/06/22.
//

#include "ColorGradient.h"


namespace Engine{

    glm::vec3 ColorGradient::getColor(glm::vec3 colorA,glm::vec3 colorB, float gradient) {
        glm::vec3 result;
        result.r = colorA.r + gradient * (colorB.r - colorA.r);
        result.g = colorA.g + gradient * (colorB.g - colorA.g);
        result.b = colorA.b + gradient * (colorB.b - colorA.b);

        return result;

    }

    glm::vec3 ColorGradient::getColor(int r,int g,int b){
        float max = 255.0f;
        float R = ((float)r)/max;
        float G = ((float)g)/max;
        float B = ((float)b)/max;
        return glm::vec3(R,G,B);
    }

}