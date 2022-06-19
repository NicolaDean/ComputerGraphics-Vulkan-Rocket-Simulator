//
// Created by nicomane on 19/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UICOMPONENT_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UICOMPONENT_H

#include "../../core/Objects/Mesh.h"
#include "../../core/Objects/Texture.h"
namespace Engine{
    class UIcomponent: public Engine::Mesh{

    protected:
        float x_pos;
        float y_pos;
        float width;
        float height;

        bool visible = false;

        Engine::Texture texture;
    public:
        UIcomponent(){};
        UIcomponent(int x,int y,int w,int h,std::string text_path,Engine::BufferManager bufferManager): Engine::Mesh(bufferManager){
            x_pos = x;
            y_pos = y;
            width = w;
            height = h;

           /* vertices ={
                    {{-0.5f,-0.5f,0.0f},{1.0f,0.0f,0.0f},{0,0}},
                    {{0.5f,-0.5f,0.0f},{1.0f,0.0f,0.0f},{1,0}},
                    {{0.5f,0.5f,0.0f},{0.0f,1.0f,0.0f},{1,1}},
                    {{-0.5f,0.5f,0.0f},{0.0f,1.0f,0.0f},{0,1}},
            };*/

            vertices ={
                    {{-0.05f,-0.02f,-0.2f},{1.0f,0.0f,0.0f},{1,1}},
                    {{0.05f,-0.02f,-0.2f},{1.0f,0.0f,0.0f},{0,1}},
                    {{0.05f,0.02f,-0.2f},{0.0f,1.0f,0.0f},{0,0}},
                    {{-0.05f,0.02f,-0.2f},{0.0f,1.0f,0.0f},{1,0}},
            };


            /*vertices ={
                     {{-width,-height,-0.2f},{1.0f,0.0f,0.0f},{1,1}},
                    {{width,-height,-0.2f},{1.0f,0.0f,0.0f},{0,1}},
                    {{width,height,-0.2f},{0.0f,1.0f,0.0f},{0,0}},
                    {{width,height,-0.2f},{0.0f,1.0f,0.0f},{1,0}},
            };*/
            indices = {0, 1, 2, 2, 3, 0};

            texture = Texture(text_path,bufferManager);

            setPos(glm::vec3(0.5,0.5,0));
        }

        /************UI METHODS*****************/
        void setVisible(){visible = true;}
        void hide(){visible = false;}
        bool isClicked(float x, float y);

        /*****VULKAN UTILS********************/
        void init();
        void close();
        void initDescriptor(DescriptorManager* descriptorManager);

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_UICOMPONENT_H
