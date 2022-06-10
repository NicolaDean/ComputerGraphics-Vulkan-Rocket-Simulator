//
// Created by nicomane on 09/06/22.
//

#include "PerlinNoise.h"


namespace Engine{

    void PerlinNoise::PerlinNoise1D(int nOctaves){
        srand(10373);
        //Octaves are the varius functions with frequency on power of 2
        for(int x=0;x<width;x++){
            float fNoise = 0.0f;
            float fScale = 1.0f; //Scale the noise
            float fScaleAcc = 0.0f;

            for(int o=0; o<nOctaves;o++){
                int nPitch = width >> o; //Divide the factor by 2 each octave (1 1/2 1/4 1/8...)
                int nSample1 = (x/ nPitch) * nPitch;
                int nSample2 = (nSample1 + nPitch) %width;

                //Calculate how far into the pitch are we
                float fBlend = (float)(x - nSample1) / (float)nPitch;

                //Calculate Linear interpolation
                float fSample = (1.0f - fBlend) * noiseSeed[nSample1] + fBlend*noiseSeed[nSample2];
                fNoise += fSample*fScale; //Accumulate noise on width
                fScaleAcc +=fScale; //Calculate current scale
                fScale = fScale/2; //Decrease the scale of 1/2 for the next octave  (1 1/2 1/4 1/8...)
            }
            perlinNoise[x] = fNoise / fScaleAcc; //(Divide by scale to be 0 and 1
        }
    }
    void PerlinNoise::PerlinNoise2D(int nOctaves){
        srand(10373);
        float bias = 1.5f;
        //Octaves are the varius functions with frequency on power of 2
        for(int x=0;x<width;x++){
            for(int y=0;y<height;y++){
                float fNoise = 0.0f;
                float fScale = 20.0f; //Scale the noise
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
    void PerlinNoise::savePerlinNoiseAsImage() {
            std::ofstream outdata; // outdata is like cin
            int i; // loop index
            int num[5] = {4, 3, 6, 7, 12}; // list of output values

            outdata.open("./build/perlinNoise.bpm"); // opens the file
            if( !outdata ) { // file couldn't be opened
                std::cout << "Error: file could not be opened" << std::endl;
                return;
            }

            //HEADER DATA
            outdata<<"P1"<<std::endl;
            outdata<<3<<" "<<width<<std::endl;
            //PIXEL DATA
            for(int x=0;x<width;x++){
                int force = (perlinNoise[x] * height);
                int y=0;
                for(y =0;y<force;y++){
                    outdata<<1<<" ";
                }
                for(int i = y;i<height-1;i++){
                    outdata<<0<<" ";
                }
                outdata<<0<<std::endl;
                //outdata << 0<<" "<<1<<" "<<0<<""<<0<<" "<<1<<" "<<1<< std::endl;
            }
            outdata.close();
        }


    void PerlinNoise::savePerlinNoiseAsImage2D() {
        std::cout<<"BANANA\n";
        std::ofstream outdata; // outdata is like cin
        outdata.open("./build/perlinNoise.pgm"); // opens the file
        if( !outdata ) { // file couldn't be opened
            std::cout << "Error: file could not be opened" << std::endl;
            return;
        }

        //HEADER DATA
        outdata<<"P2"<<std::endl;
        outdata<<height<<" "<<width<<std::endl;
        outdata<<270<<std::endl;
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