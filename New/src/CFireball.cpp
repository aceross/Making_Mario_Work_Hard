#include <unistd.h>

#include "CFireball.h"
#include "GlobalFunctions.h"

CFireball::CFireball() 
{    
    ID = ++CEntity::EntityCounter;    
    Type = 16;
    
    FollowPath = false;
    LoopPath = false;    
    
    Flags = FIREBALL_FLAGS;
    Width = FIREBALL_WIDTH;
    Height = FIREBALL_HEIGHT;
    NumberOfFrames = FIREBALL_ANIMATION_NUM_FRAMES;
    Collision_Width = FIREBALL_COLLISION_WIDTH;
    Collision_Height = FIREBALL_COLLISION_HEIGHT;
    Collision_X = FIREBALL_COLLISION_X;
    Collision_Y = FIREBALL_COLLISION_Y;
    MaxSpeedX = FIREBALL_MAXSPEED_X;
    MaxSpeedY = FIREBALL_MAXSPEED_Y;  
    ThrownBy = NULL;
    DeathDelay = 0;
}

CFireball::CFireball(CFireball* temp, int params[])
{       
    // Offset Y by Height
    temp->Y -= FIREBALL_HEIGHT;
    
    temp->Flags = FIREBALL_FLAGS;
    temp->Width = FIREBALL_WIDTH;
    temp->Height = FIREBALL_HEIGHT;
    temp->NumberOfFrames = FIREBALL_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = FIREBALL_COLLISION_WIDTH;
    temp->Collision_Height = FIREBALL_COLLISION_HEIGHT;
    temp->Collision_X = FIREBALL_COLLISION_X;
    temp->Collision_Y = FIREBALL_COLLISION_Y;
    temp->MaxSpeedX = FIREBALL_MAXSPEED_X;
    temp->MaxSpeedY = FIREBALL_MAXSPEED_Y;
    
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(FIREBALL_GFX));
    
    PopulateData(temp);
    
    ThrownBy = temp->ThrownBy;
    DeathDelay = 0;
}

bool CFireball::Load(char* File, int Width, int Height, int NumberOfFrames) 
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

bool CFireball::OnCollision(CEntity* Entity) 
{
    if (Entity != ThrownBy && Entity->Killable == true)
    {
       // Hit an enemy (or static object eg block or platform)
        int eX = Entity->X;
        int eY = Entity->Y;
        
        Entity->Kill();
        
        // Replace Enemy with a coin!!
        CreateCoin(eX, eY);
    }
    
    // Kill the Fireball too
    if (Entity->Type != ENTITY_TYPE_PLAYER)
        Kill();
        
    CEntity::OnCollision(Entity);
}

void CFireball::Animate()
{
    if (MoveLeft)
        CurrentFrameCol = FIREBALL_ANIMATION_COL_NORM;
    else if (MoveRight)
        CurrentFrameCol = FIREBALL_ANIMATION_COL_NORM + 1;
    
    CEntity::Animate();
}