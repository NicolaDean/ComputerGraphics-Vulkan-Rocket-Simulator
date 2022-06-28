//
// Created by nicomane on 08/06/22.
//

#include "Rocket.h"
#include <stdio.h>
#include <math.h>

namespace Engine{
    float PITCH_ANI = 0.05f;
    float TERM_VEL  = -2.5;
    float RSPE_MAX = 0.005;
    float RSPE_ACC = 1e-6;
    float EXPLS_SCALE = 6;
    float EXPLS_OFFSET = 1;
    float TOUT_LIGHT_FADE = 500;
    float MAX_LIGHT = 0.6f;
    float gravity=0.001f;
    float startHeight = 1.0f;


    void Rocket::trajectory(glm::vec3 target, float highMax, float vAcc) {

        target = target +pos;
        highMax -= pos[1];
        if(highMax <= 0 || highMax < target[1]){
            std::cout<<"Invalid trajectory height\n";
        }

        //Setting start height for landing
        startHeight=pos[1];

        glm::vec2 htg      = glm::vec2(target[2], target[0]);
        hdir     = glm::normalize(htg);
        float aag      = vAcc * (vAcc + gravity);
        timeout  = glm::sqrt(2 * gravity * highMax / aag);
        float aag1yh   = aag * (1 - target[1] / highMax);
        float r_aag1yh = sqrt(aag1yh);
        ttl      = timeout * (vAcc + gravity + r_aag1yh) / gravity ;
        float a2g      = vAcc * 2 + gravity;
        float isZero   = a2g - 2 * r_aag1yh;
        float xAcceleration     = isZero ? isZero / (pow(a2g,2) - 4 * aag1yh) : 1 / (2 * a2g);
        verticalAcceleration[0]  = glm::length(htg) / highMax * aag * xAcceleration;
        verticalAcceleration[1]  = vAcc + gravity;
        std::cout<<"X vertical acc:\n"<<verticalAcceleration[0]<<"\n";
        std::cout<<"Y vertical acc:\n"<<verticalAcceleration[1]<<"\n";
         launched=true;
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
       //std::cout<<"dx: "<<dh<<"\n";
       // std::cout<<"dy: "<<dv<<"\n";

    }

    void Rocket::close() {
        Model::close();
        std::cout<<"Rocket closing:";
    }
    /* Update movement */
    void Rocket::update(float dt) {
    if (launched) {

        //Can apply simple trajectory equation
        //https://en.wikipedia.org/wiki/Projectile_motion#Angle_.CE.B8_required_to_hit_coordinate_.28x.2Cy.29

        //NEW METHOD TO PRINT VEC3 (we can add in Printer all print of class helper methods)
        //Printer::print("Rocket orientation",orientation);

        //TEST THE MOVEMENTS
        orientation += glm::vec3 (1,0,0)*dt;


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

        ttl -= dt;

        // If timeout elapsed in this delta
        // update first for timeout with propulsion and
        // then turn off propulsion and update for the remaining time

        if (timeout && timeout < dt) {
            updateAcceleration(timeout);
            dt -= timeout;
            timeout = 0;
            verticalAcceleration[0] = 0;
            verticalAcceleration[1] = 0;
        } else {
            timeout -= dt;
        }

        updateAcceleration(dt);

        if (!timeout) {
            rspe += RSPE_ACC * dt;
        }
        if (rspe > RSPE_MAX) {
            rspe = RSPE_MAX;
        }
        roll += rspe * dt;
        //TODO NEED TO FIND FLOOR AND HEIGHT FOR COLLISION



        // If floor collision warp up
        if (pos[1] < startHeight) {
            launched=false;
        }



        //TODO pitch Target find correct function atan2

        /*float pitchTarget = - M_PI / 2 - glm::atan(verticalVelocity);
        if(abs(pitchTarget - pitch) > PITCH_ANI){
                     pitch += PITCH_ANI * sgn(pitchTarget - pitch);

         }
        else{
                     pitch = pitchTarget;
         }
         -------------
         THE UPDATE THESE MATRIXES

        get worldMatrix() {
            if(this._wrldMat == null)
                this._wrldMat = matrix.Mat4.transl(...this._pos)
            .mul(this._pitchyaw)
                    .mul(matrix.Mat4.rotZ(this._roll))
                    .mul(matrix.Mat4.scale(this._hvscale[0], this._hvscale[0], this._hvscale[1]));
            return this._wrldMat;
        }

        get followMatrix() {
            if(this._followMat == null)
                this._followMat = matrix.Mat4.transl(...this._pos)
            .mul(this._pitchyaw)
                    .mul(matrix.Mat4.scale(this._hvscale[0], this._hvscale[0], this._hvscale[1]));
            return this._followMat;
        }

         */


    }

    }


}