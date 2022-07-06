//
// Created by nicomane on 24/06/22.
//

#include "Skybox.h"

namespace Engine{

    std::vector<Mesh*> Skybox::sky_list;
    int Skybox::current = 0;
    void Skybox::init() {
        std::cout<<"Loading SkyBox\n";
        loadModel();
        std::cout<<"Loading SkyBox Textures\n";
        texture.loadCubic();
        std::cout<<"SkyBox Loaded\n";
        Mesh::init();
    }

    void Skybox::closeSky() {
        for(int i=0;i<sky_list.size();i++){
            if(current!=i){
                sky_list.at(i)->close();
            }
        }
    }
    void Skybox::rotateSky() {
        std::cout<<"Address SKY 1: " <<sky_list.at(current)<<"\n";
        //Remove old sky
        //std::remove(Mesh::meshes->begin(), Mesh::meshes->end(),sky_list.at(current) );
        Mesh::meshes->erase(std::remove(Mesh::meshes->begin(), Mesh::meshes->end(),sky_list.at(current)), Mesh::meshes->end());
        //Mesh::meshes->erase(Mesh::meshes->begin() + current);
        //Increment counter
        current = (current+1)%3;
        std::cout<<"Address SKY 2: " <<sky_list.at(current)<<"\n";
        //Add new sky
        Mesh::addMesh(sky_list.at(current));
    }
}