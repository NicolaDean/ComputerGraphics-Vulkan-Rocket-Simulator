#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "../engine/App.h"

namespace MyApp{
    class MyApp: public Engine::App{

    public:
        MyApp(int width,int h,std::string win_name):Engine::App(width,h,win_name){
            //Some Code....
        }

        void loop(){
            std::cout<<"Banana\n";
        }
    };
}

