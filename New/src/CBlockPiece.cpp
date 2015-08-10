#include <unistd.h>

#include "CBlockPiece.h"
#include "CSurfaceManager.h"

CBlockPiece::CBlockPiece() 
{    
    ID = ++CEntity::EntityCounter;    
    Type = 18;
    
    FollowPath = false;
    LoopPath = false;    
    
    Flags = BLOCKPIECE_FLAGS;
    Width = BLOCKPIECE_WIDTH;
    Height = BLOCKPIECE_HEIGHT;
    NumberOfFrames = BLOCKPIECE_ANIMATION_NUM_FRAMES;
    MaxSpeedX = BLOCKPIECE_MAXSPEED_X;
    MaxSpeedY = BLOCKPIECE_MAXSPEED_Y;  
    
    Animation.SetFrameRate(BLOCKPIECE_ANIMATION_FRAMERATE);
}

CBlockPiece::CBlockPiece(CEntity* temp, int params[])
{       
    // Offset Y by Height
    temp->Y -= BLOCKPIECE_HEIGHT;    
    temp->Flags = BLOCKPIECE_FLAGS;
    temp->Width = BLOCKPIECE_WIDTH;
    temp->Height = BLOCKPIECE_HEIGHT;
    temp->NumberOfFrames = BLOCKPIECE_ANIMATION_NUM_FRAMES;
    temp->MaxSpeedX = BLOCKPIECE_MAXSPEED_X;
    temp->MaxSpeedY = BLOCKPIECE_MAXSPEED_Y;
    
    Animation.SetFrameRate(BLOCKPIECE_ANIMATION_FRAMERATE);
    
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(BLOCKPIECE_GFX));
    
    PopulateData(temp);
}

bool CBlockPiece::Load(char* File, int Width, int Height, int NumberOfFrames) 
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

