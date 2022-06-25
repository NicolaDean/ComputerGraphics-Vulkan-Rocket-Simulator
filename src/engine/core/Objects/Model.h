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

    protected:
        std::string modelPath;
        Texture texture;

    public:
        Model():Mesh(){};
        Model(BufferManager buff):Mesh(buff){};

        Model(std::string model_path,std::string text_path,BufferManager buffManager):Mesh(buffManager){
            std::cout<<model_path<<"\n";
            modelPath = model_path;
            texture = Texture(text_path,buffManager);
        }

        void init();
        void initDescriptor(DescriptorManager* descriptorManager);
        virtual void update(float dt){std::cout<<"MODEL\n";}

        void close();
        Texture* getTexture(){
            return &texture;
        }

        void loadModel();
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
