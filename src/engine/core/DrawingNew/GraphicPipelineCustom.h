//
// Created by nicomane on 02/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_GRAPHICPIPELINECUSTOM_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_GRAPHICPIPELINECUSTOM_H

#include "../../commonLibs.h"
#include "../Presentation/SwapChain.h"
#include "../Drawing/DepthImage.h"
#include "DescriptorManager.h"
#include "../Geometry/Vertex.h"
namespace Engine{
    class GraphicPipelineCustom {
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkDevice* device;
        SwapChain* swapChain;

        /** FOR RECREATION **/

        std::string vertexShader;
        std::string fragmentShader;
        std::vector<DescriptorManager *> descriptors;

    public:
        static std::vector<GraphicPipelineCustom*> userPipelines;

        GraphicPipelineCustom(){};
        GraphicPipelineCustom(VkDevice * dev,SwapChain * swap){
            device = dev;
            swapChain = swap;
        };

        void createGraphicPipeline(const std::string& VertShader, const std::string& FragShader,std::vector<DescriptorManager *> D);
        void createRenderPass(DepthImage depthImage);
        void close();
        void closeRenderPass();

        void recreate(SwapChain * swap);
        VkShaderModule createShaderModule(const std::vector<char>& code);



        void setRenderPass(VkRenderPass renderP){
            renderPass = renderP;
        }

        VkRenderPass getRenderPass(){
            return renderPass;
        }

        VkExtent2D  getSwapChainExtent(){
            return swapChain->getSwapChainExtent();
        }

        VkPipeline getGraphicPipeline(){
            return graphicsPipeline;
        }

        VkPipelineLayout getPipelineLayout(){
            return pipelineLayout;
        }
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_GRAPHICPIPELINECUSTOM_H
