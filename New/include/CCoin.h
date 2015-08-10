/* 
 * File:   CCoin.h
 * Author: alan
 *
 * Created on December 7, 2012, 2:18 PM
 */

#ifndef CCOIN_H
#define	CCOIN_H

#include "CEntity.h"
#include "CPoints.h"
#include "GlobalFunctions.h"

#define COIN_ANIMATION_FRAMERATE     300
#define COIN_POINTS_EARNED           100
#define COIN_ANIMATION_NUM_FRAMES    4
#define COIN_FLAGS             12
#define COIN_WIDTH             24
#define COIN_HEIGHT            32
#define COIN_COLLISION_WIDTH   0
#define COIN_COLLISION_HEIGHT  0
#define COIN_COLLISION_X       0
#define COIN_COLLISION_Y       0
#define COIN_MAXSPEED_X        10
#define COIN_MAXSPEED_Y        10
#define COIN_GFX                        "./gfx/coin.png"

class CCoin : public CEntity
{
    public:
       
        CCoin();

        CCoin(CEntity* temp, int params[]);
        
	bool Load(char* File, int Width, int Height, int NumberOfFrames);
        
        bool OnCollision(CEntity* Entity);                
};



#endif	/* CCOIN_H */

