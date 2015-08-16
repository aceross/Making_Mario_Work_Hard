/* 
 * File:   CBlockPiece.h
 * Author: alan
 *
 * Created on February 16, 2013, 1:43 PM
 */

#ifndef CBLOCKPIECE_H
#define	CBLOCKPIECE_H

#include "CEntity.h"

#define BLOCKPIECE_ANIMATION_FRAMERATE     300
#define BLOCKPIECE_ANIMATION_NUM_FRAMES    2
#define BLOCKPIECE_FLAGS             3
#define BLOCKPIECE_WIDTH             18
#define BLOCKPIECE_HEIGHT            18
#define BLOCKPIECE_MAXSPEED_X        20
#define BLOCKPIECE_MAXSPEED_Y        20
#define BLOCKPIECE_GFX               "./gfx/blockpieces.png"

class CBlockPiece : public CEntity
{
    public:
       
        CBlockPiece();

        CBlockPiece(CEntity* temp, int params[]);
        
	bool Load(char* File, int Width, int Height, int NumberOfFrames);                      
};

#endif	/* CBLOCKPIECE_H */

