#pragma once
#include "../../commonLibs.h"
#include "../Geometry/Vertex.h"
#include "Descriptor.h"
#include "../Drawing/UniformBuffer.h"
#include "../Drawing/BufferManager.h"
#include "../Drawing/TextureManager.h"
#include "../Drawing/DepthImage.h"
namespace Engine{
    class GraphicPipeline {

    private:
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkDevice* device;
        Descriptor descriptor;
        UniformBuffer uniformBuffer;

    public:
        GraphicPipeline(){}
        GraphicPipeline(VkDevice * d){
            device = d;
            descriptor = Descriptor(d); //Associate the descriptor to the device

        }

        VkRenderPass getRenderPass(){
            return renderPass;
        }
        VkPipeline getGraphicPipeline(){
            return graphicsPipeline;
        }

        void close();
        void closeDescriptor(){descriptor.close();};
        void closeUniformBuffer(){uniformBuffer.close();};
        /**
         * Create the graphic pipeline starting from shaders
         */
        void createGraphicPipeline(VkExtent2D swapChainExtent);
        void createRenderPass(VkFormat swapChainImageFormat,DepthImage depthImage);
        void createUniformBuffers(BufferManager bufferMng){
            uniformBuffer = UniformBuffer(device,bufferMng);
            uniformBuffer.createUniformBuffers();
        };

        void createDescriptorSetLayout(){descriptor.createDescriptorSetLayout();};
        void createDescriptorPool(){descriptor.createDescriptorPool();};
        void createDescriptorSet(TextureManager textureManager){descriptor.createDescriptorSets(&uniformBuffer,textureManager);};
        void updateUniformBuffer(uint32_t currentImage,VkExtent2D swapChainExtent){
            uniformBuffer.updateUniformBuffer(currentImage,swapChainExtent);
        };
        /**
         * Create the vulkan struct to declare the Pipeline Shaders stage of a Shared module
         * @param module  module of which create the Pipeline stage
         * @return  vulkan create info struct
         */
        VkPipelineShaderStageCreateInfo createPipelineShaderStage(VkShaderModule module);

        /**
         * Return the vulkan struct relative of a shader module
         * @param code code of a sheader read from file
         * @return vulkan create info struct
         */
        VkShaderModule createShaderModule(const std::vector<char>& code);



        std::vector<VkDescriptorSet> getDescriptorSets(){
            return descriptor.getDescriptorSets();
        }

        VkPipelineLayout getPipelineLayout(){
            return pipelineLayout;
        }
    };
}



