//
// Created by nicomane on 09/06/22.
//

#ifndef COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PERLINNOISE_H
#define COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PERLINNOISE_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>

namespace Engine{
    class PerlinNoise {
        int width;
        int height;
    public:
        //srand (time(NULL));
        float* noiseSeed = nullptr;
        float* perlinNoise = nullptr;

        float* noiseSeed2D = nullptr;
        float* perlinNoise2D = nullptr;

        PerlinNoise(int X, int Y){

            width=X;
            height=Y;

            noiseSeed = new float [width];
            perlinNoise = new float[width];

            noiseSeed2D = new float[width * height];
            perlinNoise2D = new float[width * height];

            for(int i=0;i<width;i++) {
                noiseSeed[i] = (float)rand() / (float)RAND_MAX;
            }

            for(int i=0;i<width*height;i++) {
                noiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
            }

        }

        void PerlinNoise1D(int nOctaves);
        void PerlinNoise2D(int nOctaves);

        //https://en.wikipedia.org/wiki/Netpbm
        void savePerlinNoiseAsImage();
        void savePerlinNoiseAsImage2D();
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PERLINNOISE_H
