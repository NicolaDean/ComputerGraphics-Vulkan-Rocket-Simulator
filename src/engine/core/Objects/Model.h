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
        bool isClone = false;
    public:
        Model():Mesh(){};
        Model(BufferManager buff):Mesh(buff){};

        Model(std::string model_path,std::string text_path,BufferManager buffManager):Mesh(buffManager){
            std::cout<<"CREATE : " <<model_path<<"\n";
            modelPath = model_path;
            texture = Texture(text_path,buffManager);
        }

        Model(std::vector<Vertex>vert,std::vector<uint32_t> ind,BufferManager buffManager,Texture txt):Mesh(buffManager){
            vertices = vert;
            indices = ind;
            texture = txt;
        }

        void init();
        void initDescriptor(DescriptorManager* descriptorManager);
        Model * cloneModel(BufferManager buff,DescriptorManager* desc);
        virtual void update(float dt){std::cout<<"MODEL\n";}

        void close();
        Texture* getTexture(){
            return &texture;
        }

        void loadModel();
        void initClone();
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MODEL_H
