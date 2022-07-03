//
// Created by nicomane on 01/07/22.
//

#include "Light.h"

namespace Engine{
    std::vector<Light*> Light::sceneLights;

    void Light::getPointLight(LightUniform * uniform) {
        uniform->color  = color;
        uniform->pos    = pos;
    }

    void Light::update(float dt) {

    }

}