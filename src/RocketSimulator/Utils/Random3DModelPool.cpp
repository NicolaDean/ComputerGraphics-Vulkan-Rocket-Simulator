//
// Created by nicomane on 25/06/22.
//

#include "Random3DModelPool.h"

namespace Engine{

    void Random3DModelPool::init() {
        int size = modelPaths.size();
        std::cout<<"3d MODEL POOL NAMES:\n";
        for(int i=0;i<size;i++){
            std::cout<<modelPaths[i]<<"\n";
        }
    }


    void Random3DModelPool::generatePool(int poolsize) {
        srand(SEED);
        poolSize = poolsize;
        for(auto selector: modelPaths){
            std::cout<<selector<<"\n";
            Model* m = new Model(selector,"./src/Textures/desert.jpeg",bufferManager);
            models.push_back(m);
        }
    }

    std::vector<Model*> Random3DModelPool::initModels(GraphicPipelineCustom* pipeline, DescriptorManager* descriptor) {

        for(auto m: models){
            m->init();
            m->setScale(0.5);
            m->setPos(glm::vec3(0,4,0));
            m->initDescriptor(descriptor);
            m->bindPipeline(pipeline);
            Mesh::addMesh(m);
        }

        int size = modelPaths.size();
        //LIKE A SORT OF INSTANCE RENDERING WE CLONE VERICES OF MODEL AND ONLY RECREATE DESCRIPTOR SET
        for(int i=0;i<poolSize;i++){
            int model_selector = (int)(((float)rand() / (float)RAND_MAX)*size);
            Model * clone  = models.at(model_selector)->cloneModel(bufferManager,descriptor);
            models.push_back(clone);

        }

        return  models;
    }

}
