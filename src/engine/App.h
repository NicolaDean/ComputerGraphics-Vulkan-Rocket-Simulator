//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_APP_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_APP_H
#include "core/Core.h"
#include "core/Objects/Mesh.h"
#include "core/Objects/Model.h"
#include "core/Objects/Camera.h"
#include "core/Utils/printHelper.h"

namespace Engine{

    /**
     * App class will contail all engine method public to the user (us)
     * For example methods to change views, to setup Camera, Load Models......
     */
    class App: public Engine::Core {

    protected:

    public:
        std::vector<Entity*>* movableEntities;
        App(int width,int h,std::string win_name):Core(width,h,win_name){
            movableEntities = new  std::vector<Entity*>();
        }

        void updateScene(uint32_t currentImage);
        void updateCamera(float dt);
        void updateMeshesPos(int currentFrame);
        void customInit();


        void subscribeMovable(Mesh *  entity){
            movableEntities->push_back(entity);
        }
        //TODO DO AN UNSUBSCRIBE METHOD

        //void addMesh(); -> other idea, add mesh to APP( example a vector) so we can loop through models
    };
}

#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_APP_H
