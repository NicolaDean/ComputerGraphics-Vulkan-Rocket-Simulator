//
// Created by nicomane on 24/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SKYBOX_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SKYBOX_H

#include "../../engine/core/Objects/Model.h"

namespace Engine{
    class Skybox:public Model {

        std::string  texturePath;
    public:
        Skybox(BufferManager buff,std::string texturePath): Model(buff){
            modelPath = "./src/Models/SkyBoxCube.obj";
            texture = Texture(texturePath,buff);
            texturePath = texturePath;

            notCalculateWorldMatrix();
            modelMatrix = Camera::currentCam->getPerspectiveMatric() * Camera::currentCam->getCamPosTranslate();
        }

        void init();

        void loadCubicTexture(){

        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SKYBOX_H
