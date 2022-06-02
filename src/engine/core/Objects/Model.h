//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
#include "../../commonLibs.h"
#include "Mesh.h"
#include "../Geometry/Vertex.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace Engine{
    class Model: public Mesh {

        std::string modelPath;
    public:

        Model(std::string model_path){
            modelPath = model_path;
        }

        void init();
        void loadModel();

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
