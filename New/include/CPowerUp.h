/* 
 * File:   CPowerUp.h
 * Author: alan
 *
 * Created on January 8, 2013, 1:32 PM
 */

#ifndef CPOWERUP_H
#define	CPOWERUP_H

#include "CEntity.h"
#include "GlobalFunctions.h"

#define POWERUP_POINTS_EARNED                   1000
#define POWERUP_ANIMATION_NUM_FRAMES            1
#define POWERUP_FIRE_ANIMATION_NUM_FRAMES       2
#define POWERUP_FLAGS             5
#define POWERUP_WIDTH             32
#define POWERUP_HEIGHT            32
#define POWERUP_COLLISION_WIDTH   0
#define POWERUP_COLLISION_HEIGHT  0
#define POWERUP_COLLISION_X       0
#define POWERUP_COLLISION_Y       0
#define POWERUP_MAXSPEED_X        10
#define POWERUP_MAXSPEED_Y        10
#define POWERUP_GFX               "./gfx/powerups.png"

enum
{
    POWERUP_TYPE_GREEN,                 // 0
    POWERUP_TYPE_RED,                   // 1        
    POWERUP_TYPE_FIREFLOWER             // 2
};

class CPowerUp : public CEntity
{
    public:
       
        CPowerUp();

        CPowerUp(CEntity* temp, int params[]);
        
	bool Load(char* File, int Width, int Height, int NumberOfFrames);

        void Animate();

        bool OnCollision(CEntity* Entity);    
        
        void ChangePowerUpType(int Type);
        
        int OriginalPowerupType;
        int PowerUpType;
};

#endif	/* CPOWERUP_H */

