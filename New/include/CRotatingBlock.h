/* 
 * File:   CRotatingBlock.h
 * Author: alan
 *
 * Created on January 22, 2013, 4:01 PM
 */

#ifndef CROTATINGBLOCK_H
#define	CROTATINGBLOCK_H

#include "CBlock.h"
#include "GlobalFunctions.h"

#define ROTATION_TIME   3000

class CRotatingBlock : public CBlock
{
    public:
        CRotatingBlock();
        
        CRotatingBlock(CEntity* temp, int params[]);
        
        void LoadSettings();
        
        void Animate();
        bool OnCollision(CEntity* Entity);    
        void Kill();
        void Loop();
        
    private:
        void BreakBlock();
        void CreateBlockPiece(int x, int y, int sX, int sY);
        bool Rotating;
        int  RotatingTime;
};


#endif	/* CROTATINGBLOCK_H */

