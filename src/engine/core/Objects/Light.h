//
// Created by nicomane on 01/07/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
#include "../../commonLibs.h"
#include "Entity.h"
#include "../Geometry/UniformBufferObject.h"
namespace Engine{

    class Light : public Entity{

    public:
        static std::vector<Light*> sceneLights;

        glm::vec3 color;

        Light(){}

        Light(glm::vec3 lightPos,glm::vec3 lightColor){
            pos = lightPos;
            color = lightColor;
            sceneLights.push_back(this);
        }

        void getPointLight(LightUniform * uniform);
        virtual void update(float dt);
    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
