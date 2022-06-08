//
// Created by nicomane on 08/06/22.
//

#include "Rocket.h"
#include <stdio.h>
#include <math.h>

namespace Engine{
    float PITCH_ANI = 0.05f;
    float TERM_VEL  = -2.5;
    float RSPE_MAX = .005;
    float RSPE_ACC = 1e-6;
    float EXPLS_SCALE = 6;
    float EXPLS_OFFSET = 1;
    float TOUT_LIGHT_FADE = 500;
    float MAX_LIGHT = 0.6f;

    void Rocket::trajectory(glm::vec3 target, float highMax, float vAcc) {

        float gravity = 9.81; //we can set global variables and one of these is gravity
        target = target +pos;
        highMax -= pos.y;
        if(highMax <= 0 || highMax < target.y){
            std::cout<<"Invalid trajectory height\n";
        }

        glm::vec2 htg      = glm::vec2(target.z, target.x);
        hdir     = glm::normalize(htg);
        float aag      = vAcc * (vAcc + gravity);
        timeout  = glm::sqrt(2 * gravity * highMax / aag);
        float aag1yh   = aag * (1 - target.y / highMax);
        float r_aag1yh = sqrt(aag1yh);
        ttl      = timeout * (vAcc + gravity + r_aag1yh) / gravity ;
        float a2g      = vAcc * 2 + gravity;
        float isZero   = a2g - 2 * r_aag1yh;
        float xAcceleration     = isZero ? isZero / (pow(a2g,2) - 4 * aag1yh) : 1 / (2 * a2g);
        verticalAcceleration[0]  = glm::length(htg) / highMax * aag * xAcceleration;
        verticalAcceleration[1]  = vAcc + gravity;
    };

    /* MAYBE BETTER IN UTILS */
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    /* Update the accelerating components */
    void Rocket::updateAcceleration(float dt) {
        float g = 9.81;
        verticalVelocity.x += (verticalAcceleration.x    ) * dt;
        verticalVelocity.y += (verticalAcceleration.y - g) * dt;
        if(verticalVelocity.y < TERM_VEL)
            verticalVelocity.y = TERM_VEL;
        float dh = verticalVelocity.x * dt - (verticalAcceleration.x    ) / 2 * pow(dt,2);
        float dv = verticalVelocity.y * dt - (verticalAcceleration.y - g) / 2 * pow(dt,2);
        pos.x += dh * hdir.y;
        pos.z += dh * hdir.x;
        pos.y += dv;
    }

    /* Update movement */
    void Rocket::update(float dt) {
        //std::cout<<"Rocket update\n";
        if(!launched){
            return;
        }
        /*TODO Convert in C++
        //const pos_old = [...pos];
        //const {floor: floor0} = this._globals.collision.findFloorHeight(...pos_old);

        // If out of bounds
        if(floor == null) {
            deleted = true;
            return;
        }
         */

        /*TODO Invalid previous matrix
        wrldMat = null;
        followMat = null;

        */
        ttl  -= dt;
        // If timeout elapsed in this delta
        // update first for timeout with propulsion an
        // then turn off propulsion and update for the remaining time
        if(timeout && timeout < dt) {
            updateAcceleration(timeout);
            dt -= timeout;
            timeout = 0;
            verticalAcceleration.x = verticalAcceleration.y = 0;
        }
        else
            timeout -= dt;
        updateAcceleration(dt);
        if(!timeout)
            rspe += RSPE_ACC * dt;
        if(rspe > RSPE_MAX)
            rspe = RSPE_MAX;
        roll += rspe * dt;
        /*TODO NEED TO FIND FLOOR AND HEIGHT FOR COLLISION
        float floor;
        float height;

        // If out of bounds
        if(floor == null) {
            position(...pos_old);
            verticalVelocity.x = 0;
            verticalAcceleration.x = 0;
            verticalAcceleration.y = 0;
        }

        // If floor collision warp up
        if(pos.y < height) {
            pos.y = height + hscale * EXPLS_OFFSET;
            deleted = true;
            //Add explosion after deleting the rocket
            //TODO
        }
         */

        /*
         * TODO pitchTatget find correct function atan2

        float pitchTarget = - M_PI / 2 - glm::atan(verticalVelocity);
        if(abs(pitchTarget - pitch) > PITCH_ANI){
                     pitch += PITCH_ANI * sgn(pitchTarget - pitch);

         }
        else{
                     pitch = pitchTarget;

         }
                */
    }


}