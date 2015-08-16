/* 
 * File:   CPoints.h
 * Author: alan
 *
 * Created on December 7, 2012, 2:18 PM
 */

#ifndef CPOINTS_H
#define	CPOINTS_H

#include "CEntity.h"
#include "SDL_ttf.h"

#define POINTS_ANIMATION_NUM_FRAMES 1
#define POINTS_FLAGS             3
#define POINTS_COLLISION_WIDTH   0
#define POINTS_COLLISION_HEIGHT  0
#define POINTS_COLLISION_X       0
#define POINTS_COLLISION_Y       0
#define POINTS_MAXSPEED_X        10
#define POINTS_MAXSPEED_Y        10

class CPoints : public CEntity
{
    public:
        
        CPoints();

        CPoints(CPoints* temp);
        
	bool Load(char* File, int Width, int Height, int NumberOfFrames);
        void Tidy();
};

#endif	/* CPOINTS_H */

