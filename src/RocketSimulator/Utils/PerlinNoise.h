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
        int SEED;
    public:
        //srand (time(NULL));
        float* noiseSeed = nullptr;
        float* perlinNoise = nullptr;

        float* noiseSeed2D = nullptr;
        float* perlinNoise2D = nullptr;


        PerlinNoise(){}
        PerlinNoise(int X, int Y){
            width=X+1;
            height=Y+1;
        }

        /**************UTILS************************/
        void setSeed(int s){SEED = s;};
        float getNoise(int x,int y);
        void clean();
        void init();
        /**************PERLIN NOISE******************/
        void generate2DPerlinNoise(int nOctaves);
        void savePerlinNoiseAsImage2D();
        //https://en.wikipedia.org/wiki/Netpbm
    };
}



#endif //COMPUTERGRAPHICS_VULKAN_ROCKET_SIMULATOR_PERLINNOISE_H
