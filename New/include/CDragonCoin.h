/* 
 * File:   CDragonCoin.h
 * Author: alan
 *
 * Created on February 5, 2013, 11:44 AM
 */

#ifndef CDRAGONCOIN_H
#define	CDRAGONCOIN_H

#include "CCoin.h"

#define DRAGONCOIN_ANIMATION_FRAMERATE     100
#define DRAGONCOIN_POINTS_EARNED           500
#define DRAGONCOIN_ANIMATION_NUM_FRAMES    5
#define DRAGONCOIN_FLAGS             2
#define DRAGONCOIN_WIDTH             34
#define DRAGONCOIN_HEIGHT            52
#define DRAGONCOIN_COLLISION_WIDTH   0
#define DRAGONCOIN_COLLISION_HEIGHT  0
#define DRAGONCOIN_COLLISION_X       0
#define DRAGONCOIN_COLLISION_Y       0
#define DRAGONCOIN_MAXSPEED_X        10
#define DRAGONCOIN_MAXSPEED_Y        10
#define DRAGONCOIN_GFX               "./gfx/dragoncoin.png"

class CDragonCoin : public CCoin
{
    public:
        CDragonCoin();
        CDragonCoin(CEntity* temp, int params[]);
        bool OnCollision(CEntity* Entity);
};

#endif	/* CDRAGONCOIN_H */

