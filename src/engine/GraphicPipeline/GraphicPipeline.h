#pragma once
#include "../commonLibs.h"

namespace Engine{
    class GraphicPipeline {

    private:
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkDevice* device;

    public:
        GraphicPipeline(){}
        GraphicPipeline(VkDevice* d){
            device = d;
        }

        VkRenderPass getRenderPass(){
            return renderPass;
        }
        VkPipeline getGraphicPipeline(){
            return graphicsPipeline;
        }

        void close();


        /**
         * Create the graphic pipeline starting from shaders
         */
        void createGraphicPipeline(VkExtent2D swapChainExtent);
        void createRenderPass(VkFormat swapChainImageFormat);

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



    };
}



