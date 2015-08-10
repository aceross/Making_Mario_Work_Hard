/* 
 * File:   CStretchBlock.h
 * Author: alan
 *
 * Created on February 19, 2013, 3:04 PM
 */

#ifndef CSTRETCHBLOCK_H
#define	CSTRETCHBLOCK_H

#include "CEntity.h"

#define STRETCHBLOCK_FLAGS              8
#define STRETCHBLOCK_WIDTH              32
#define STRETCHBLOCK_HEIGHT             32
#define STRETCHBLOCK_COLLISION_WIDTH    0
#define STRETCHBLOCK_COLLISION_HEIGHT   0
#define STRETCHBLOCK_COLLISION_X        0
#define STRETCHBLOCK_COLLISION_Y        0
#define STRETCHBLOCK_GFX                "./gfx/rotatingblock.png"

#define STRETCHBLOCK_NUM_OF_BLOCKS      5
#define STRETCHBLOCK_ANIM_SPEED         10
#define STRETCHBLOCK_PAUSETIME          1500

struct StretchBlock
{
    float X;
    float Y;
    bool  Stopped;
    bool  AtMiddle;    
};

class CStretchBlock : public CEntity
{
    public:
        
        CStretchBlock();
        CStretchBlock(CEntity* temp, int params[]);
        
        void LoadSettings();  
        
        void Render(SDL_Surface* SDisplay, int X2Offset);
        void Animate();
        bool OnCollision(CEntity* Entity);            
        void Loop();    
        
    private:
        
        int             Direction; // 1=IN -1=OUT
        int             MiddleBlock;
        StretchBlock    Blocks[STRETCHBLOCK_NUM_OF_BLOCKS];
        bool            Paused;
        bool            Stopped;
        
        int MoveTime;
        int PauseTime;
    
        void    ContractBlocks();
        void    ExpandBlocks();        
};

#endif	/* CSTRETCHBLOCK_H */

