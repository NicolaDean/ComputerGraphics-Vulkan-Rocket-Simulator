//
// Created by nicomane on 01/07/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
#include "../../commonLibs.h"
#include "Entity.h"
#include "../Geometry/UniformBufferObject.h"
namespace Engine{

    struct AmbientLight{
        glm::vec3 lightDir;
        glm::vec4 lightColor;
    };

    class Light : public Entity{

    public:
        static AmbientLight ambient;
        static std::vector<Light*> sceneLights;
        static int numOfLights;

        glm::vec4 color;

        Light(){}

        Light(glm::vec3 lightPos,glm::vec4 lightColor){
            pos = lightPos;
            color = lightColor;
            sceneLights.push_back(this);
            numOfLights++;
        }

        void getPointLight(LightUniform * uniform);
        static void setAmbientLight(glm::vec3 direction,glm::vec4 color);
        virtual void update(float dt);
        glm::vec3 getPos(){return pos;};
    };
}


#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_LIGHT_H
