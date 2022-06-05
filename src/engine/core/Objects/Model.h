//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
#include "../../commonLibs.h"
#include "Mesh.h"
#include "../Geometry/Vertex.h"


namespace Engine{
    class Model: public Mesh {

        std::string modelPath;
    public:
        Model():Mesh(){}
        Model(std::string model_path,BufferManager buffManager):Mesh(buffManager){
            modelPath = model_path;
        }

        void init();
        void loadModel();
        void customUpdate(float ft){

        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
