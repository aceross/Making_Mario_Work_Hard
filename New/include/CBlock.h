/* 
 * File:   CBlock.h
 * Author: alan
 *
 * Created on January 23, 2013, 2:43 PM
 */

#ifndef CBLOCK_H
#define	CBLOCK_H

#include "CEntity.h"
#include "GlobalFunctions.h"
#include "CCoin.h"
#include "CBeanStalk.h"

class CBlock : public CEntity
{
    public:
        CBlock();

        virtual void Initialize(CEntity* temp, int params[]);
        
	virtual bool Load(char* File, int Width, int Height, int NumberOfFrames);     

        virtual void Animate();

        virtual bool OnCollision(CEntity* Entity);    
    
        bool Opened;
        int  Contains;

    protected:
        // ENTITY SPECIFIC CONSTANT SETTINGS           
        int CONST_ANIMATION_NUM_FRAMES_OPENED;     
        int CONST_ANIMATION_COL_OPENED;     
        int CONST_ANIMATION_ROW_OPENED;   
        
};

#endif	/* CBLOCK_H */

