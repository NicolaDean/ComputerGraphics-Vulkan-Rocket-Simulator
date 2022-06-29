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

        void (*action)();

        float near_plane = 0.2;
        bool visible = false;


        Engine::Texture texture;
    public:
        UIcomponent(){};
        UIcomponent(float x,float y,float w,float h,std::string text_path,void (*a)(),BufferManager bufferManager): Mesh(bufferManager){
            x_pos = x;
            y_pos = y;
            width = w;
            height = h;

            action = a;
            initVertices(x,y,w/(float)2,h/(float)2);
           /* vertices ={
                    {{-0.05f,-0.02f,-0.2f},{1.0f,0.0f,0.0f},{1,1}},
                    {{0.05f,-0.02f,-0.2f},{1.0f,0.0f,0.0f},{0,1}},
                    {{0.05f,0.02f,-0.2f},{0.0f,1.0f,0.0f},{0,0}},
                    {{-0.05f,0.02f,-0.2f},{0.0f,1.0f,0.0f},{1,0}},
            };*/

            indices = {0, 1, 2, 2, 3, 0};

            texture = Texture(text_path,bufferManager);

            setPos(glm::vec3(0.5,0.5,0));
        }

        void initVertices(float x,float y,float w,float h);

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
