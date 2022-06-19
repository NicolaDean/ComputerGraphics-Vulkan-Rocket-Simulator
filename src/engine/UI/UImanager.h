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
    public:
        static UImanager interface;
        UImanager(){};


        /*******GLOBAL METHODS******/
        static void addComponent(UIcomponent* comp){
            UImanager::interface.components.push_back(comp);
        }

        static  std::vector<UIcomponent*> getUI(){
            return UImanager::interface.components;
        }

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UIMANAGER_H
