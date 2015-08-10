/* 
 * File:   CFireball.h
 * Author: alan
 *
 * Created on February 6, 2013, 9:49 AM
 */

#ifndef CFIREBALL_H
#define	CFIREBALL_H

#include "CEntity.h"

#define FIREBALL_ANIMATION_COL_NORM     0
#define FIREBALL_ANIMATION_NUM_FRAMES   1
#define FIREBALL_FLAGS             2
#define FIREBALL_WIDTH             30
#define FIREBALL_HEIGHT            16
#define FIREBALL_COLLISION_WIDTH   0
#define FIREBALL_COLLISION_HEIGHT  0
#define FIREBALL_COLLISION_X       0
#define FIREBALL_COLLISION_Y       0
#define FIREBALL_MAXSPEED_X        12
#define FIREBALL_MAXSPEED_Y        0
#define FIREBALL_GFX               "./gfx/fireball.png"

class CFireball : public CEntity
{
    public:
        CFireball();
        CFireball(CFireball* temp, int params[]);
        
	bool Load(char* File, int Width, int Height, int NumberOfFrames);        
        bool OnCollision(CEntity* Entity);
        void Animate();
        
        CEntity*    ThrownBy;
        
};

#endif	/* CFIREBALL_H */

