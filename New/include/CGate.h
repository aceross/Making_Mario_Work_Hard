/* 
 * File:   CGate.h
 * Author: alan
 *
 * Created on February 6, 2013, 2:31 PM
 */

#ifndef CGATE_H
#define	CGATE_H

#include "CEntity.h"

#define GATE_FLAGS             10
#define GATE_ANIMATION_NUM_FRAMES    1
#define GATE_COLLISION_WIDTH   0
#define GATE_COLLISION_HEIGHT  0
#define GATE_COLLISION_X       0
#define GATE_COLLISION_Y       0
#define GATE_MAXSPEED_X        0
#define GATE_MAXSPEED_Y        0

#define MIDWAY_GATE_GFX        "./gfx/midwaygate.png"
#define MIDWAY_WIDTH           48
#define MIDWAY_HEIGHT          150
#define MIDWAY_SECTION_HEIGHT  16

#define GIANT_GATE_GFX          "./gfx/giantgate.png"
#define GIANT_WIDTH             96
#define GIANT_HEIGHT            300
#define GIANT_SECTION_HEIGHT    32

enum {
    GATE_TYPE_NONE,
    GATE_TYPE_GIANT,
    GATE_TYPE_MIDWAY
};

class CGate : public CEntity
{
    public:
        CGate();
        CGate(CEntity* temp, int params[]);
        
	bool Load(std::string File, int Width, int Height, int NumberOfFrames);
        void Tidy();
        
        std::string     Gate_Gfx;
        int             SectionHeight;        
        int             GateType; // 1=GIANT 2=MIDWAY
};

#endif	/* CGATE_H */

