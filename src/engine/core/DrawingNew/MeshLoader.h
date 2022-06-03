//
// Created by nicomane on 03/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESHLOADER_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESHLOADER_H

#include "../../commonLibs.h"
#include "../Objects/Mesh.h"
#include "../Objects/Model.h"
#include "../Objects/Texture.h"
#include "../Drawing/BufferManager.h"
#include "DescriptorManager.h"
#include "../Geometry/UniformBufferObject.h"
#include "GraphicPipelineCustom.h"

namespace Engine{
    class MeshLoader {

        Model model;
        Texture texture;
        DescriptorManager descManager;
        GraphicPipelineCustom graphicPipeline;
    public:
        MeshLoader(BufferManager manager,SwapChain* swapChain){

        }

        void load();
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_MESHLOADER_H
