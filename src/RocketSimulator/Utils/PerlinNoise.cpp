//
// Created by nicomane on 09/06/22.
//

#include "PerlinNoise.h"


namespace Engine{

    float PerlinNoise::getNoise(int x, int y) {

        //CHECK IF THIS POINT IS OUTSIDE THE GRID
        if(x<0 || x >= width) return 0;
        if(y<0 || y >= height) return 0;

        float res = noiseSeed2D[y*width +x]; //Dynamic programming (have value already stored)

        return res;
    }

    void PerlinNoise::init() {
        noiseSeed2D = new float[width * height];
        perlinNoise2D = new float[width * height];

        srand(SEED);

        //Initialize Noises Vector
        for(int i=0;i<width*height;i++) {
            //noiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
            noiseSeed2D[i] = ((float)rand() / (float)RAND_MAX)*2.0f - 1.0f; //Values between -1 and 1
        }
    }

    void PerlinNoise::generate2DPerlinNoise(int nOctaves){

        float bias = 1.5f;
        //Octaves are the varius functions with frequency on power of 2
        for(int x=0;x<width;x++){
            for(int y=0;y<height;y++){
                float fNoise = 0.0f;
                float fScale = 200.0f; //Scale the noise
                float fScaleAcc = 0.0f;

                for(int o=0; o<nOctaves;o++) {
                    int nPitch = width >> o; //Divide the factor by 2 each octave (1 1/2 1/4 1/8...)
                    int sampleX1 = (x / nPitch) * nPitch;
                    int sampleY1 = (y / nPitch) * nPitch;

                    int sampleX2 = (sampleX1 + nPitch) % width;
                    int sampleY2 = (sampleY1 + nPitch) % width;

                    //Calculate how far into the pitch are we
                    float fBlendx = (float) (x - sampleX1) / (float) nPitch;
                    float fBlendy = (float) (y - sampleY1) / (float) nPitch;

                    //Calculate Linear interpolation
                    float fSampleT = (1.0f - fBlendx) * noiseSeed2D[sampleY1 * width + sampleX1] +
                                     fBlendx * noiseSeed2D[sampleY1 * width + sampleX2];
                    float fSampleB = (1.0f - fBlendx) * noiseSeed2D[sampleY2 * width + sampleX1] +
                                     fBlendx * noiseSeed2D[sampleY2 * width + sampleX2];

                    fNoise += (fBlendy * (fSampleB - fSampleT) + fSampleT) * fScale; //Accumulate noise on width
                    fScaleAcc += fScale; //Calculate current scale
                    fScale = fScale / bias; //Decrease the scale of 1/2 for the next octave  (1 1/2 1/4 1/8...)
                }
                perlinNoise2D[y*width +x] = fNoise / fScaleAcc; //(Divide by scale to be 0 and 1
            }
        }

        std::cout<<"Ended Perlin Noise:\n";
    }

    void PerlinNoise::savePerlinNoiseAsImage2D() {
        std::cout<<"Saving Perling Noise\n";
        std::ofstream outdata; // outdata is like cin
        outdata.open("./build/perlinNoise.pgm"); // opens the file
        if( !outdata ) { // file couldn't be opened
            std::cout << "Error: file could not be opened" << std::endl;
            return;
        }

        //HEADER DATA
        outdata<<"P2"<<std::endl;
        outdata<<height<<" "<<width<<std::endl;
        outdata<<500<<std::endl;
        //PIXEL DATA
        int count = 0;
        for(int x=0;x<width;x++){
            outdata<<"#ROW: "<<x<<"\n";
           for(int y=0;y<height;y++){
               int pixel =(int) ((float)perlinNoise2D[width*y + x]*(float)255);
               if(pixel>255) pixel =255;
               if(pixel<0) pixel=0;
               outdata<<pixel;
               count++;
               if(y == height-1){
                   outdata << "\n";
                   count = 0;
               }else{
                   outdata << " ";
               }
               /*if(count == 70){
                   std::cout<<"NEW LINE\n";
                   outdata << "\n";
                   count = 0;
               }else{
                   outdata << " ";
               }*/
           }
        }
        outdata.close();
        std::cout<<"OOOOOOK\n";
    }

}