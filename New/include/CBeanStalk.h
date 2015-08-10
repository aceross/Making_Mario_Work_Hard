/* 
 * File:   CBeanStalk.h
 * Author: alan
 *
 * Created on December 18, 2012, 9:41 AM
 */

#ifndef CBEANSTALK_H
#define	CBEANSTALK_H

#include "CEntity.h"

#define BEANSTALK_FLAGS             2
#define BEANSTALK_WIDTH             57
#define BEANSTALK_HEIGHT            36
#define BEANSTALK_ANIMATION_NUM_FRAMES    1
#define BEANSTALK_COLLISION_WIDTH   0
#define BEANSTALK_COLLISION_HEIGHT  0
#define BEANSTALK_COLLISION_X       0
#define BEANSTALK_COLLISION_Y       0
#define BEANSTALK_MAXSPEED_X        0
#define BEANSTALK_MAXSPEED_Y        0
#define BEANSTALK_GFX                    "./gfx/beanstalk.png"

class CBeanStalk : public CEntity 
{
    public:
        CBeanStalk();

        CBeanStalk(CEntity* temp, int params[]);
        
	bool Load(std::string File, int Width, int Height, int NumberOfFrames);
        void Loop();        
        void Tidy();
        bool OnCollision(CEntity* Entity);
        
        int  MaxHeight;
        bool Growing;
        
    private:
        float MinY;       
        int PreviousTime;
};

#endif	/* CBEANSTALK_H */

