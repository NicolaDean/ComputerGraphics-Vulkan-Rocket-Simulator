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

        float gravity = 0.001; //we can set global variables and one of these is gravity
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
        float g = 0.001;
        verticalVelocity[0] += (verticalAcceleration[0]    ) * dt;
        verticalVelocity[1] += (verticalAcceleration[1] - g) * dt;
        if(verticalVelocity[1] < TERM_VEL){
            verticalVelocity[1] = TERM_VEL;

        }
        float dh = verticalVelocity[0] * dt - (verticalAcceleration[0]    ) / 2 * pow(dt,2);
        float dv = verticalVelocity[1] * dt - (verticalAcceleration[1] - g) / 2 * pow(dt,2);
        pos[0] += dh * hdir[1];
        pos[2] += dh * hdir[0];
        pos[1] += dv;

    }

    void Rocket::close() {
        Model::close();
        std::cout<<"Rocket closing:";
    }
    /* Update movement */
    void Rocket::update(float dt) {
        setUpdated();//Set the "hasBeenUpdated" flag to update the matrix

        //Can apply simple trajectory equation
        //https://en.wikipedia.org/wiki/Projectile_motion#Angle_.CE.B8_required_to_hit_coordinate_.28x.2Cy.29

        //NEW METHOD TO PRINT VEC3 (we can add in Printer all print of class helper methods)
        //Printer::print("Rocket orientation",orientation);

        //TEST THE MOVEMENTS
        //pos += glm::vec3 (0,1,0)*dt;


        //check if clicked launch button
        /*
        if(!launched){
            return;
        }
         */


        //TEST ORIENTATION CHANGES
        //pos += glm::vec3(0.0f,1.0f,0.0f)*dt;


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
        // update first for timeout with propulsion and
        // then turn off propulsion and update for the remaining time

        if(timeout && timeout < dt) {
            updateAcceleration(timeout);
            dt -= timeout;
            timeout = 0;
            verticalAcceleration.x = verticalAcceleration.y = 0;
        }
        else{
            timeout -= dt;
        }


        updateAcceleration(dt);

       // pos += glm::vec3(0.0f,1.0f,0.0f)*dt;

        if(!timeout)
            rspe += RSPE_ACC * dt;
        if(rspe > RSPE_MAX)
            rspe = RSPE_MAX;
        roll += rspe * dt;
        /*TODO NEED TO FIND FLOOR AND HEIGHT FOR COLLISION
        float height=1.0f;



        // If floor collision warp up
        if(pos[1] < height) {
            pos[1] = height + hscale * EXPLS_OFFSET;
            deleted = true;
            //Add explosion after deleting the rocket
            //TODO
        }



         * TODO pitch Tatget find correct function atan2

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