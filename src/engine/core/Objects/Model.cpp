//
// Created by nicomane on 02/06/22.
//

#include "Model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace Engine{

    void Model::init() {
        loadModel();
        texture.load();
        Mesh::init();
    }

    void Model::initClone(){
        isClone = true;
        Mesh::init();
    }

    void Model::initDescriptor(DescriptorManager* descriptorManager) {
        descriptorManager->pushElementDescriptor({0, UNIFORM, sizeof(UniformBufferObject), nullptr});
        descriptorManager->pushElementDescriptor({1, TEXTURE, 0, &texture});
        descriptorSets = descriptorManager->createAndGetDescriptorSets(&uniformBufferManager);
    }

    Model* Model::cloneModel(BufferManager buff,DescriptorManager* desc){
        Model *m = new Model(vertices,indices,buff,texture);
        m->initClone();
        m->initDescriptor(desc);
        m->bindPipeline(pipeline);
        Mesh::addMesh(m);
        return m;
    }

    void Model::close() {
        Mesh::close();
        if(!isClone) {
            texture.clean();
        }
        std::cout<<"Close model "<<modelPath<<"\n";
    }

    void Model::loadModel() {
        //TODO CONVERT THIS FUNCTION INTO A STATIC METHOD (like an OBJ system)
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                              modelPath.c_str())) {
            throw std::runtime_error(warn + err);
        }

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                vertex.pos = {
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2]
                };

                vertex.texCoord = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        1 - attrib.texcoords[2 * index.texcoord_index + 1]
                };

                vertex.norm = {
                        attrib.normals[3 * index.normal_index + 0],
                        attrib.normals[3 * index.normal_index + 1],
                        attrib.normals[3 * index.normal_index + 2]
                };

                vertices.push_back(vertex);
                indices.push_back(vertices.size()-1);
            }
        }
    }
}