//
// Created by nicomane on 03/06/22.
//

#include "MeshLoader.h"


namespace Engine{
    void MeshLoader::load() {
        descManager.createDescriptorPool();

        descManager.pushBindingDescriptor({0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT});
        descManager.pushBindingDescriptor({1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT});

        descManager.getDescriptorSetLayout();

        descManager.pushElementDescriptor({0, UNIFORM, sizeof(UniformBufferObject), nullptr});
        descManager.pushElementDescriptor({1, TEXTURE, 0, &texture});

        descManager.createDescriptorSets();
    }
}