#include <unistd.h>

#include "CPoints.h"
#include "CAreaScoring.h"

CPoints::CPoints() 
{       
    ID = ++CEntity::EntityCounter;    
    Type = 5;    
    FollowPath = false;
    LoopPath = false;
    LifeSpan = 1000;    

    Flags = POINTS_FLAGS;
    NumberOfFrames = POINTS_ANIMATION_NUM_FRAMES;
    Collision_Width = POINTS_COLLISION_WIDTH;
    Collision_Height = POINTS_COLLISION_HEIGHT;
    Collision_X = POINTS_COLLISION_X;
    Collision_Y = POINTS_COLLISION_Y;
    MaxSpeedX = POINTS_MAXSPEED_X;
    MaxSpeedY = POINTS_MAXSPEED_Y;
    
    SetInitialSpeed(0, -25, 0 , 0);    
}

CPoints::CPoints(CPoints* temp)
{       
    temp->Flags = POINTS_FLAGS;
    temp->NumberOfFrames = POINTS_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = POINTS_COLLISION_WIDTH;
    temp->Collision_Height = POINTS_COLLISION_HEIGHT;
    temp->Collision_X = POINTS_COLLISION_X;
    temp->Collision_Y = POINTS_COLLISION_Y;
    temp->MaxSpeedX = POINTS_MAXSPEED_X;
    temp->MaxSpeedY = POINTS_MAXSPEED_Y;
    
    PopulateData(temp);
}

bool CPoints::Load(char* File, int Width, int Height, int NumberOfFrames) 
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

void CPoints::Tidy()
{
    if (SEntity)
        SDL_FreeSurface(SEntity);
    
    SEntity = NULL;
}