/* 
 * File:   CGateBar.h
 * Author: alan
 *
 * Created on February 7, 2013, 9:29 AM
 */

#ifndef CGATEBAR_H
#define	CGATEBAR_H

#include "CEntity.h"
#include "CGate.h"

#define GATEBAR_FLAGS             13
#define GATEBAR_COLLISION_WIDTH   0
#define GATEBAR_COLLISION_HEIGHT  0
#define GATEBAR_COLLISION_X       0
#define GATEBAR_COLLISION_Y       0
#define GATEBAR_MAXSPEED_X        0
#define GATEBAR_MAXSPEED_Y        4

#define GATEBAR_MIDWAY_WIDTH      24
#define GATEBAR_MIDWAY_HEIGHT     8
#define GATEBAR_MIDWAY_GFX        "./gfx/midwaygatebar.png"

#define GATEBAR_GIANT_WIDTH       48
#define GATEBAR_GIANT_HEIGHT      16
#define GATEBAR_GIANT_GFX         "./gfx/giantgatebar.png"

class CGateBar : public CEntity
{
    public:
        CGateBar();
        CGateBar(CGateBar* temp);
        
	bool Load(std::string File, int Width, int Height, int NumberOfFrames);        
        bool OnCollision(CEntity* Entity);
        
        int GateType; // 1=GIANT 2=MIDWAY
        std::string     Bar_Gfx;
        int             BarHeight, BarWidth;  
        int             BottomY, TopY;
        
        bool            PointsCollected;
        bool            MidwayReached;
        
        CGate*          ParentGate;
};

#endif	/* CGATEBAR_H */

