/* 
 * File:   CPButton.h
 * Author: alan
 *
 * Created on February 23, 2013, 2:21 PM
 */

#ifndef CPBUTTON_H
#define	CPBUTTON_H

#include "CEntity.h"

#define PBUTTONFLAGS                    1
#define PBUTTONANIMATION_NUM_FRAMES     2
#define PBUTTON_SECONDSTATE_TIME_LIMIT  500

#define PBUTTON_COLLISION_WIDTH   0
#define PBUTTON_COLLISION_HEIGHT  0
#define PBUTTON_COLLISION_X       0
#define PBUTTON_COLLISION_Y       0
#define PBUTTON_MAXSPEED_X      0
#define PBUTTON_MAXSPEED_Y      0

#define PBUTTON_COLLISION_Y_SECONDSTATE 18

#define PBUTTON_GFX              "./gfx/pbutton.png"
#define PBUTTON_WIDTH           32
#define PBUTTON_HEIGHT          32

class CPButton : public CEntity
{
    public:
        CPButton();

        CPButton(CEntity* temp, int params[]);
        
        bool Load(std::string File, int Width, int Height, int NumberOfFrames) ;
        void Loop();   
        void Animate();
        bool OnCollision(CEntity* Entity);
        
        bool Activated;
        bool SecondState;        
};


#endif	/* CPBUTTON_H */

