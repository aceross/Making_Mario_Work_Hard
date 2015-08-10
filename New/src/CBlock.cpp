#include <unistd.h>

#include "CBlock.h"
#include "CCoin.h"
#include "CBeanStalk.h"
#include "CSoundManager.h"
        
CBlock::CBlock() 
{    

}

void CBlock::Initialize(CEntity* temp, int params[])
{   
    // parameter 0: Contains
    
    // If param is > 0 it represents the ID of a linked entity
    // If param = -1 then produce coin
    // If param = -2 then produce Red Mushroom
    Contains = (params[0] == -999) ? 0 : params[0];
    
    Opened = false;
    
    // Offset Y by Height
    temp->Y -= CONST_HEIGHT;

    temp->MaxY = temp->Y;
    
    temp->Flags = CONST_FLAGS;
    temp->Width = CONST_WIDTH;
    temp->Height = CONST_HEIGHT;
    temp->NumberOfFrames = CONST_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = CONST_COLLISION_WIDTH;
    temp->Collision_Height = CONST_COLLISION_HEIGHT;
    temp->Collision_X = CONST_COLLISION_X;
    temp->Collision_Y = CONST_COLLISION_Y;
    temp->MaxSpeedX = CONST_MAXSPEED_X;
    temp->MaxSpeedY = CONST_MAXSPEED_Y;
    temp->ZIndex= 1;
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(CONST_GFX));
    
    PopulateData(temp);            
}

bool CBlock::Load(char* File, int Width, int Height, int NumberOfFrames) 
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

void CBlock::Animate() 
{    
    if (Opened)
    {
        // Change box appearance
        CurrentFrameCol = CONST_ANIMATION_COL_OPENED;
        CurrentFrameRow = CONST_ANIMATION_ROW_OPENED;
        Animation.SetNumberOfFrames(CONST_ANIMATION_NUM_FRAMES_OPENED);        
    }
    
    Animation.SetFrameRate(CONST_ANIMATION_FRAMERATE);    
    CEntity::Animate();
}

bool CBlock::OnCollision(CEntity* Entity) 
{
    if ((!Opened) && (Entity->Type == ENTITY_TYPE_PLAYER) && (Above(Entity, true)))
    {
        // Box has been hit from below by the Player
        Opened = true;

        CanJump = true;
        Jump();
        
        CSoundManager::SoundManager.Play(FX_BREAK_BLOCK);
        
        // Check for Linking via Contains
        if (Contains)       
            switch (Contains)
            {
                case -1:
                    // Display a coin
                    CreateCoin(X, Y);
                    break;
                    
                default: // an Entity ID has been provided
                    
                    CEntity* ent = GetEntityByID(Contains);
                    
                    if (ent)
                        switch (ent->Type)
                        {
                            case ENTITY_TYPE_BEANSTALK:
                                ent->X = (X + (Width/2)) - (ent->Width / 2);
                                ent->Y = Y + 10;
                                ((CBeanStalk*)ent)->Growing = true;
                                break;
                                
                            case ENTITY_TYPE_POWERUP:
                                ent->X = X + 10;
                                ent->Y = Y - 40;                              
                                ent->SetInitialSpeed(-15,-15,0,0);
                                
                                CSoundManager::SoundManager.Play(FX_POWERUP_APPEARS);
                                break;
                        }                        
                    
                    break;                
            }            
    }
    
    return true;
}
