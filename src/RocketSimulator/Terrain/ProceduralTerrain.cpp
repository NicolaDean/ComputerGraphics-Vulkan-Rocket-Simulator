//
// Created by nicomane on 12/06/22.
//

#include "ProceduralTerrain.h"


namespace Engine{

    //Retrieves noise from PerlinNoise2Da
    float ProceduralTerrain::getNoise(int x, int y) {
        return noises.getNoise(x,y);
    }

    //Get Terrain Height based on neighboirs noise and height
    float ProceduralTerrain::getHeight(int x, int y) {
        //TODO add the Interpolation code and add light so we can use single color
        return terrainSmoothing(x,y)*1;
    }

    glm::vec3 ProceduralTerrain::calculateNormal(int x, int z) {
        float heightL = getHeightMod(x - 1, z);
        float heightR = getHeightMod(x + 1, z);
        float heightD = getHeightMod(x, z - 1);
        float heightU = getHeightMod(x, z + 1);
        glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
        normal = glm::normalize(normal);
        return normal;
    }

    float ProceduralTerrain::getHeightMod(int x, int z) {
        x = x < 0 ? 0 : x;
        z = z < 0 ? 0 : z;
        x = x >=  SIZE ? SIZE - 1 : x;
        z = z >= SIZE ? SIZE - 1 : z;
        return getHeight(x,z);
    }

    //TODO CREATE A GRADIENT CLASS FOR COLORSa
    glm::vec3 ProceduralTerrain::getColor(int x, int y) {
        return calculateNormal(x,y);
        /*float noise = getNoise(x,y);
        //#abc32f	(171,195,47)
        glm::vec3 C1 = ColorGradient::getColor(171,195,47);
        //	#607c3c	(96,124,60)
        glm::vec3 C2 = ColorGradient::getColor(96,124,60);
        //45% red, 35% green and 20% blue.
        return ColorGradient::getColor(glm::vec3(0.45,0.35,0.2),glm::vec3(0.66,0.5,0.2),noise);
        return glm::vec3(0.45,0.35,0.2);*/
    }
    void ProceduralTerrain::close() {
        noises.clean();
        Mesh::close();
        std::cout<<"Terrain closing:\n";
    }

    float ProceduralTerrain::terrainSmoothing(int x, int y) {
        //DO AVERAGE ON NEAR VERTEX HEIGHT
        //TOP VERTEX
        float topLeft   = getNoise(x-1,y-1);
        float topCenter = getNoise(x,y-1);
        float topRight  = getNoise(x+1,y-1);
        //BOTTOM
        float bottomLeft    = getNoise(x-1,y+1);
        float bottomCenter  = getNoise(x,y+1);
        float bottomRight   = getNoise(x+1,y+1);
        //SIDE
        float left  = getNoise(x-1,y);
        float right = getNoise(x+1,y);

        //CORNERS
        float smoothedVertexCorners = 0;
        smoothedVertexCorners += topLeft;
        smoothedVertexCorners += topRight;
        smoothedVertexCorners += bottomLeft;
        smoothedVertexCorners += bottomRight;
        smoothedVertexCorners = smoothedVertexCorners/16.0f;
        //SIDES
        float smoothedVertexSides = 0;
        smoothedVertexSides += topCenter;
        smoothedVertexSides += bottomCenter;
        smoothedVertexSides += right;
        smoothedVertexSides += left;
        smoothedVertexSides = smoothedVertexSides/4.0f;
        //Center
        float smoothCenter = getNoise(x,y)/4.0f;

        return smoothedVertexSides + smoothedVertexCorners + smoothCenter;
    }

}