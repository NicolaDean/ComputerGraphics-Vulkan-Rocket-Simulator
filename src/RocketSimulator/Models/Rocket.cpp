//
// Created by nicomane on 08/06/22.
//

#include "Rocket.h"


namespace Engine{

    void Rocket::update(float dt) {

        this->pos += glm::vec3(0,1,1) * dt;
        std::cout<<"BANANA";
    }
}