/* 
 * File:   CPlatform.h
 * Author: alan
 *
 * Created on December 13, 2012, 2:32 PM
 */

#ifndef CPLATFORM_H
#define	CPLATFORM_H

#include "CEntity.h"

#define PLATFORM1_WIDTH             96
#define PLATFORM1_HEIGHT            32
#define PLATFORM1_X                 0

#define PLATFORM2_WIDTH             128
#define PLATFORM2_HEIGHT            22
#define PLATFORM2_X                 96

#define PLATFORM3_WIDTH             160
#define PLATFORM3_HEIGHT            22
#define PLATFORM3_X                 224

#define PLATFORM_FLAGS                  0
#define PLATFORM_ANIMATION_NUM_FRAMES   1
#define PLATFORM_COLLISION_WIDTH        0
#define PLATFORM_COLLISION_HEIGHT       0
#define PLATFORM_COLLISION_X            0
#define PLATFORM_COLLISION_Y            0
#define PLATFORM_MAXSPEED_X             2
#define PLATFORM_MAXSPEED_Y             2
#define PLATFORM_GFX                    "./gfx/platforms.png"

class CPlatform : public CEntity 
{
    public:
        CPlatform();

        CPlatform(CEntity* temp, int params[]);
        
	bool Load(std::string File, int Width, int Height, int NumberOfFrames);
        void Render(SDL_Surface* SDisplay, int X2Offset);
        bool OnCollision(CEntity* Entity);
        
        int  PlatformType;
        
    private:
        int pHeight, pWidth, pX, pY;
};

#endif	/* CPLATFORM_H */

