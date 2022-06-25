//
// Created by nicomane on 11/06/22.
//

#include "Plane.h"
#include "../../engine/core/Utils/printHelper.h"
namespace Engine{

    void Plane::init() {
        std::cout<<"INITIALIZED PLANE"<<"\n";
        generatePlane();
        Mesh::init();
    }

    void Plane::generatePlane() {

        //GEN VERTICES
        for(int y=0;y<resolutionY;y++){
            for(int x=0;x<resolutionX;x++){
                Vertex v;
                float posX = ((float)x/((float)resolutionX -1)) * SIZE;
                float posY = ((float)y/((float)resolutionY -1)) * SIZE;
                float noise = ((float)rand() / (float)RAND_MAX)*0.5f;

                //TODO add a Random Color in gradient and apply it to normal
                v.pos = glm::vec3(posX, getHeight(posX,posY),posY);//TODO, create a "getHeight" function so i can overwrite it in terrain Generator
                //Allow also to load images onto the plane
                v.norm = getColor(posX,posY);
                v.texCoord = glm::vec2(0,0);
                vertices.push_back(v);
            }
        }


        //GEN INDEXES
        for(int y=0;y<resolutionY-1;y++){
            //increment lines
            int currentIndex = y*resolutionX;//current line
            int nextIndex = y*(resolutionX)+resolutionX;//Next line

            for(int x=0;x<resolutionX-1;x++){
                //First triangle ( I,I+1,N+1)
                indices.push_back(currentIndex);
                indices.push_back(nextIndex);
                indices.push_back(nextIndex+1);
                //std::cout<<std::dec<<"A:("<<nextIndex<<","<<currentIndex<<","<<currentIndex+1<<")\n";
                //Second triangle (N,N+1,I+1)
                indices.push_back(nextIndex+1);
                indices.push_back(currentIndex+1);
                indices.push_back(currentIndex);
                //std::cout<<std::dec<<"B:("<<nextIndex<<","<<nextIndex+1<<","<<currentIndex+1<<")\n";

                currentIndex++;
                nextIndex++;
            }
        }
    }
    float Plane::getHeight(int x, int y) {
        return 0;
    }

    glm::vec3 Plane::getColor(int x, int y) {
        return glm::vec3(0.0f,1.0f,0.0f);
    }
}