#include <unistd.h>

#include "../include/CCoin.h"
#include "../include/CAreaScoring.h"
#include "../include/CSoundManager.h"

CCoin::CCoin()
{
    ID = ++CEntity::EntityCounter;
    Type = 3;

    FollowPath = false;
    LoopPath = false;

    Flags = COIN_FLAGS;
    Width = COIN_WIDTH;
    Height = COIN_HEIGHT;
    NumberOfFrames = COIN_ANIMATION_NUM_FRAMES;
    Collision_Width = COIN_COLLISION_WIDTH;
    Collision_Height = COIN_COLLISION_HEIGHT;
    Collision_X = COIN_COLLISION_X;
    Collision_Y = COIN_COLLISION_Y;
    MaxSpeedX = COIN_MAXSPEED_X;
    MaxSpeedY = COIN_MAXSPEED_Y;
    Points = COIN_POINTS_EARNED;

    Animation.SetFrameRate(COIN_ANIMATION_FRAMERATE);
}

CCoin::CCoin(CEntity* temp, int params[])
{
    // Offset Y by Height
    temp->Y -= COIN_HEIGHT;

    if (temp->Flags == 0) // Nothing passed so use default
        temp->Flags = COIN_FLAGS;

    temp->Width = COIN_WIDTH;
    temp->Height = COIN_HEIGHT;
    temp->NumberOfFrames = COIN_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = COIN_COLLISION_WIDTH;
    temp->Collision_Height = COIN_COLLISION_HEIGHT;
    temp->Collision_X = COIN_COLLISION_X;
    temp->Collision_Y = COIN_COLLISION_Y;
    temp->MaxSpeedX = COIN_MAXSPEED_X;
    temp->MaxSpeedY = COIN_MAXSPEED_Y;
    temp->Points = COIN_POINTS_EARNED;

    Animation.SetFrameRate(COIN_ANIMATION_FRAMERATE);

    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(COIN_GFX));

    PopulateData(temp);
}

bool CCoin::Load(char* File, int Width, int Height, int NumberOfFrames)
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;

    return true;
}

bool CCoin::OnCollision(CEntity* Entity)
{
    if ((Entity->Type == ENTITY_TYPE_PLAYER) && !Dead)
    {
        // Kill coin
        Kill();

        //Move it away NOW
        int OldX = X;
        X = -100;

        // Add Coin value to score
        CAreaScoring::AreaScoring.AddCoin(1);
        CAreaScoring::AreaScoring.AddPoints(Points);

        // Display Points
        ShowPoints(Points, OldX, Y);

        //RemoveFromList();

        // Play Sound
        CSoundManager::SoundManager.Play(FX_COIN);
    }

    return true;
}
