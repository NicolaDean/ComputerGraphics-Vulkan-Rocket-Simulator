//
// Created by nicomane on 11/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PRINTHELPER_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PRINTHELPER_H

#include "../../commonLibs.h"
#include "../Geometry/Vertex.h"
namespace Engine{
    class Printer {

    public:
        static void print(glm::vec3 v){
            std::cout<<"Vec: ("<<v.x<<","<<v.y<<","<<v.z<<")\n";
        }

        static void print(std::string name,glm::vec3 v){
            std::cout<<name<<": ("<<v.x<<","<<v.y<<","<<v.z<<")\n";
        }

        static void print(std::string name,Vertex v){
            std::cout<<name<<": ("<<v.pos.x<<","<<v.pos.y<<","<<v.pos.z<<")\n";
        }
        //TODO add print of other usefull things

    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PRINTHELPER_H
