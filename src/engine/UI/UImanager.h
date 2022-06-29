//
// Created by nicomane on 19/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UIMANAGER_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UIMANAGER_H

#include "../commonLibs.h"
#include "components/UIcomponent.h"
namespace Engine{
    class UImanager {
        std::vector<UIcomponent*> components;
        BufferManager bufferManager;
        GraphicPipelineCustom* pipeline;
        DescriptorManager* descriptorManager;
    public:
        static UImanager interface;
        UImanager(){};
        UImanager(BufferManager bufferMng,GraphicPipelineCustom* pipelineCustom,DescriptorManager* desc){
            bufferManager = bufferMng;
            pipeline = pipelineCustom;
            descriptorManager = desc;
        }


        /*******GLOBAL METHODS******/
        static void init(BufferManager bufferManager,GraphicPipelineCustom* pipelineCustom,DescriptorManager* desc){
            interface = UImanager(bufferManager,pipelineCustom,desc);
        }

        static void close(){
            for(auto component : interface.components){
                component->close();
            }
        }


        static void addButton(std::string texture_path,std::function<void()> action,float x, float y, float w, float h);

        static void addComponent(UIcomponent* comp){
            UImanager::interface.components.push_back(comp);
        }

        static  std::vector<UIcomponent*> getUI(){
            return UImanager::interface.components;
        }

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UIMANAGER_H
