/* 
 * File:   CEnemy.h
 * Author: alan
 *
 * Created on January 24, 2013, 11:01 AM
 */

#ifndef CENEMY_H
#define	CENEMY_H

#include "CEntity.h"
#include "CPoints.h"

class CEnemy : public CEntity
{
    public:
        CEnemy();

        virtual void Initialize(CEntity* temp, int params[]);
        
	virtual bool Load(char* File, int Width, int Height, int NumberOfFrames);
           
        virtual void Loop();

        virtual void Tidy();

        virtual void Animate();

        virtual bool OnCollision(CEntity* Entity);    
    
        bool SecondState;
        
    protected:        
        virtual void GoSecondState(bool scorePoints = true);
        virtual void GoFirstState();
        virtual void Kill();
        
        unsigned int SecondStateTime;        

    protected:
        // ENTITY SPECIFIC CONSTANT SETTINGS           
        int CONST_ANIMATION_NUM_FRAMES_SECONDSTATE;
        int CONST_ANIMATION_COL_SECONDSTATE;
        int CONST_ANIMATION_ROW_SECONDSTATE;
        int CONST_COLLISION_Y_SECONDSTATE;
        int CONST_SECONDSTATE_TIME_LIMIT;
        int CONST_MAXSPEED_X_SECONDSTATE;
        int CONST_LEFT_FRAMECOL;
        int CONST_RIGHT_FRAMECOL;
        
        bool HasSecondState;
        bool DiesInSecondState;
};

#endif	/* CENEMY_H */

