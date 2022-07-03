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

        glm::vec4 color;

        Light(){}

        Light(glm::vec3 lightPos,glm::vec4 lightColor){
            pos = lightPos;
            color = lightColor;
            sceneLights.push_back(this);
        }

        void getPointLight(LightUniform * uniform);
        virtual void update(float dt);

        glm::vec3 getPos(){return pos;};
    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
