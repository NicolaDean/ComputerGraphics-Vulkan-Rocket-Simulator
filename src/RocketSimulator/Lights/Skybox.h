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
        static std::vector<Mesh*> sky_list;
        static int current;
        Skybox(BufferManager buff,std::string texturePath): Model(buff){
            modelPath = "./src/Models/SkyBoxCube.obj";
            texture = Texture(texturePath,buff);
            texturePath = texturePath;

            notCalculateWorldMatrix();
            modelMatrix = Camera::currentCam->getPerspectiveMatric() * Camera::currentCam->getCamPosTranslate();
            Skybox::sky_list.push_back(this);
        }

        void init();
        static void rotateSky(){
            //Remove old sky
            std::remove(Mesh::meshes->begin(), Mesh::meshes->end(), sky_list.at(current));

            //Increment counter
            current = (current+1)%3;
            //Add new sky
            Mesh::addMesh(sky_list.at(current));
        }
        void loadCubicTexture(){

        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_SKYBOX_H
