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


    std::vector<Model*> Random3DModelPool::generatePool(int poolSize) {
        srand(SEED);
        std::vector<Model*> pool;

        int size = modelPaths.size();
        for(int i=0;i<poolSize;i++){
            int model_selector = (int)(((float)rand() / (float)RAND_MAX)*size);
            std::cout<<modelPaths[model_selector]<<"\n";
            Model* m = new Model(modelPaths[model_selector],"./src/Textures/desert.jpeg",bufferManager);
            pool.push_back(m);
        }

        return  pool;
    }
}
