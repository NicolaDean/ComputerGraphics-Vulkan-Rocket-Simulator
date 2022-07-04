//
// Created by nicomane on 01/07/22.
//

#include "Light.h"

namespace Engine{
    std::vector<Light*> Light::sceneLights;
    AmbientLight Light::ambient;
    int Light::numOfLights = 0;

    void Light::getPointLight(LightUniform * uniform) {
        uniform->color  = color;
        uniform->pos    = pos;
    }

    void Light::update(float dt) {

    }

    void Light::setAmbientLight(glm::vec3 direction, glm::vec4 color) {
        ambient.lightDir = direction;
        ambient.lightColor = color;
    }

}