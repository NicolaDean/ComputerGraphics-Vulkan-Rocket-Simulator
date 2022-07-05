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
    float gravity=0.1f;


    void Rocket::trajectory(glm::vec3 target, float heightMax, float vAcc) {
        target -= pos;
        maxHeight=heightMax;
        offsetHeight = heightMax - pos[1];

        if(offsetHeight <= 0 || offsetHeight < target[1]){
            std::cout<<"Invalid trajectory height\n";
            return;
        }


        //Setting start height for landing
        startHeight=pos[1];

        glm::vec2 htg      = glm::vec2(target[2], target[0]);
        hdir     = glm::normalize(htg);
        float aag      = vAcc * (vAcc + gravity);
        timeout  = glm::sqrt(2 * gravity * heightMax / aag);
        float aag1yh   = aag * (1 - target[1] / heightMax);
        float r_aag1yh = sqrt(aag1yh);
        ttl      = timeout * (vAcc + gravity + r_aag1yh) / gravity ;
        float a2g      = vAcc * 2 + gravity;
        float isZero   = a2g - 2 * r_aag1yh;
        float xAcceleration     = isZero ? isZero / (pow(a2g,2) - 4 * aag1yh) : 1 / (2 * a2g);
        verticalAcceleration[0]  = glm::length(htg) / heightMax * aag * xAcceleration;
        verticalAcceleration[1]  = vAcc + gravity;
        std::cout<<"X vertical acc:\n"<<verticalAcceleration[0]<<"\n";
        std::cout<<"Y vertical acc:\n"<<verticalAcceleration[1]<<"\n";
        //launched=true;
    };

    void Rocket::checkPosition(){
        // If floor collision warp up
        if (pos[1] < startHeight) {
            launched=false;
        }

        if(pos[1]>=(maxHeight+startHeight)*0.9 && landing==false){
            //std::cout<<"ttl:"<<ttl<<"\n";
            //std::cout<<"llll::"<<ttl*offsetHeight*90<<"\n";

            landingFactory= glm::length(hdir)/((offsetHeight)*90);
            landingFactorx= (pitch + M_PI)/((offsetHeight)*90);

            landing=true;
        }
    }
    /* MAYBE BETTER IN UTILS */
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    /* Update the accelerating components */
    void Rocket::updateAcceleration(float dt) {
        verticalVelocity[0] += (verticalAcceleration[0]    ) * dt;
        verticalVelocity[1] += (verticalAcceleration[1] - gravity) * dt;
        if(verticalVelocity[1] < TERM_VEL){
            verticalVelocity[1] = TERM_VEL;

        }
        float dh = verticalVelocity[0] * dt - (verticalAcceleration[0]    ) / 2 * pow(dt,2);
        float dv = verticalVelocity[1] * dt - (verticalAcceleration[1] - gravity) / 2 * pow(dt,2);
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
            Printer::print("Rocket orientation",orientation);



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

            checkPosition();

            float pitchTarget = - M_PI / 2 - atan2(verticalVelocity[1],verticalVelocity[0]);
            //std::cout<<"IF :"<<abs(pitchTarget-pitch)<<"\n";

            if(abs(pitchTarget - pitch) > PITCH_ANI){
                pitch += PITCH_ANI * sgn(pitchTarget - pitch);
                //std::cout<<"SIGN :"<<sgn(pitchTarget - pitch)<<"\n";

            }else{
                pitch = pitchTarget;
                //std::cout<<"TARGET :"<<(pitchTarget)<<"\n";

            }
            //std::cout<<"PITCH:"<<pitch<<"\n";
            //std::cout<<"ROLL:"<<pitch<<"\n";
            //std::cout<<"HDIR:"<<hdir[1]<<"\n";


            //ON X is the vertical position
            //setAngles(glm::vec3(hdir[0],hdir[0],roll));


            if(landing==false){
                setAngles(glm::vec3(pitch + M_PI,glm::length(hdir),roll));
            }else if(orientation[0]-landingFactorx>0){
                orientation -= glm::vec3(landingFactorx,landingFactory,0);

            }else if(orientation[1]-landingFactory>0){
                //std::cout<<"HDIR:"<<orientation[0]<<"\n";

                    orientation -= glm::vec3(0,landingFactory,0);
                }
                else{
                    setAngles(glm::vec3(0,0,roll));
                }

                /*
                 * OR
                 * if(landing==false){
            setAngles(glm::vec3(hdir[0],hdir[0],roll));
                    }else{
            if(orientation[1]-landingFactor>0){
                orientation -= glm::vec3(landingFactor,landingFactor,0);
            }
            else{
                setAngles(glm::vec3(0,0,roll));
            }
                     }
                 */




        }


    }


}