//
// Created by nicomane on 19/06/22.
//

#include "UImanager.h"


namespace Engine{
    UImanager UImanager::interface = UImanager();

    void UImanager::addButton(std::string texture_path, float x, float y, float w, float h) {
        UIcomponent * button = new UIcomponent(x,y,w,h,texture_path,interface.bufferManager);
        button->init();
        button->bindPipeline(interface.pipeline);
        button->initDescriptor(interface.descriptorManager);
        addComponent(button);
    }
}