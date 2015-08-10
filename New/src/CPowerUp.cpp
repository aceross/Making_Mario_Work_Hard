#include <unistd.h>

#include "CPowerUp.h"
#include "CAreaScoring.h"
#include "CSoundManager.h"

CPowerUp::CPowerUp() 
{    
    ID = ++CEntity::EntityCounter;    
    Type = ENTITY_TYPE_POWERUP;
    
    FollowPath = false;
    LoopPath = false;    
    
    Flags = POWERUP_FLAGS;
    Width = POWERUP_WIDTH;
    Height = POWERUP_HEIGHT;
    NumberOfFrames = POWERUP_ANIMATION_NUM_FRAMES;
    Collision_Width = POWERUP_COLLISION_WIDTH;
    Collision_Height = POWERUP_COLLISION_HEIGHT;
    Collision_X = POWERUP_COLLISION_X;
    Collision_Y = POWERUP_COLLISION_Y;
    MaxSpeedX = POWERUP_MAXSPEED_X;
    MaxSpeedY = POWERUP_MAXSPEED_Y;  
    Points = POWERUP_POINTS_EARNED;
}

CPowerUp::CPowerUp(CEntity* temp, int params[])
{       
    // parameter 0: MushroomType
    PowerUpType = params[0];
    
    OriginalPowerupType = PowerUpType;
    
    // Offset Y by Height
    temp->Y -= POWERUP_HEIGHT;

    // params[1] = Float=1 
    if (params[1] == 1)
        temp->MaxY = temp->Y;
    
    temp->Flags = POWERUP_FLAGS;
    temp->Width = POWERUP_WIDTH;
    temp->Height = POWERUP_HEIGHT;
    temp->NumberOfFrames = POWERUP_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = POWERUP_COLLISION_WIDTH;
    temp->Collision_Height = POWERUP_COLLISION_HEIGHT;
    temp->Collision_X = POWERUP_COLLISION_X;
    temp->Collision_Y = POWERUP_COLLISION_Y;
    temp->MaxSpeedX = POWERUP_MAXSPEED_X;
    temp->MaxSpeedY = POWERUP_MAXSPEED_Y;
    temp->Points = POWERUP_POINTS_EARNED;
    
    if (PowerUpType == POWERUP_TYPE_FIREFLOWER)
        temp->NumberOfFrames = POWERUP_FIRE_ANIMATION_NUM_FRAMES;
    
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(POWERUP_GFX));
    
    PopulateData(temp);
    
    Animation.SetCurrentFrame(0);
}

bool CPowerUp::Load(char* File, int Width, int Height, int NumberOfFrames) 
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

void CPowerUp::Animate() 
{    
    CurrentFrameCol = PowerUpType;
    
    CEntity::Animate();
}

bool CPowerUp::OnCollision(CEntity* Entity) 
{    
    if ((Entity->Type == ENTITY_TYPE_PLAYER) && !Dead)
    {             
        // Kill Power-up
        Kill();
        
        //Move it away NOW
        int OldX = X;
        X = -100;
        
        CMario* player = GetPlayer();
        
        switch(PowerUpType)
        {
            case POWERUP_TYPE_GREEN: // gain 1 Life                
                CAreaScoring::AreaScoring.AddLife(1);   
                
                // Play Sound
                CSoundManager::SoundManager.Play(FX_1UP);
    
                break;
              
            case POWERUP_TYPE_RED: // become SUPER Mario
                
                if (SUPER_MARIO > player->MarioState)
                    player->ChangeMarioState(SUPER_MARIO);
                else // Store it for later
                {
                    player->ReservePowerUp = PowerUpType;
                    
                    // Play Sound
                    CSoundManager::SoundManager.Play(FX_RESERVE_STORED);
                }
                
                break;            
                
            case POWERUP_TYPE_FIREFLOWER: // become SUPER Mario 
                
                if (FIRE_MARIO > player->MarioState)
                    player->ChangeMarioState(FIRE_MARIO);

                break;                  
        }
        
        // Add Power-up value to score        
        CAreaScoring::AreaScoring.AddPoints(Points);
        
        // Display Points
        ShowPoints(Points, OldX, Y);
        
        RemoveFromList();
    }
   
    return true;
}

void CPowerUp::ChangePowerUpType(int Type)
{
    switch (Type)
    {
        case POWERUP_TYPE_FIREFLOWER:
            Animation.NumberOfFrames = POWERUP_FIRE_ANIMATION_NUM_FRAMES;
            break;
        default:
            Animation.NumberOfFrames = POWERUP_ANIMATION_NUM_FRAMES;
            break;
    }
    
    PowerUpType = Type;
}