/* 
 * File:   CPipe.h
 * Author: alan
 *
 * Created on January 17, 2013, 10:50 AM
 */

#ifndef CPIPE_H
#define	CPIPE_H

#include "CEntity.h"
#include "GlobalFunctions.h"

#define PIPE_ANIMATION_FRAMERATE                300
#define PIPE_ANIMATION_NUM_FRAMES               1
#define PIPE_FLAGS             0
#define PIPE_WIDTH             60
#define PIPE_COLLISION_WIDTH   0
#define PIPE_COLLISION_HEIGHT  0
#define PIPE_COLLISION_X       0
#define PIPE_COLLISION_Y       0
#define PIPE_MAXSPEED_X        0
#define PIPE_MAXSPEED_Y        0
#define PIPE_GFX               "./gfx/pipes.png"

class CPipe : public CEntity
{
    public:
        CPipe();

        CPipe(CEntity* temp, int params[]);
        
	bool Load(char* File, int Width, int Height, int NumberOfFrames);

        void Loop();

        void Render(SDL_Surface* SDisplay, int X2Offset);

        void Tidy();

        void Animate();

        bool OnCollision(CEntity* Entity);    
        
        int Direction, Colour;
        int Destination;
        
        void Transport(CEntity* Entity);
};



#endif	/* CPIPE_H */

