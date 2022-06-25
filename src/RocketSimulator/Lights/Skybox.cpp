//
// Created by nicomane on 24/06/22.
//

#include "Skybox.h"

namespace Engine{

    void Skybox::init() {
        std::cout<<"Loading SkyBox\n";
        loadModel();
        std::cout<<"Loading SkyBox Textures\n";
        texture.loadCubic();
        std::cout<<"SkyBox Loaded\n";

    }
}