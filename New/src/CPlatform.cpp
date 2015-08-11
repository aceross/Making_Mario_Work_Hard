
#include "../include/CPlatform.h"

CPlatform::CPlatform()
{
    Type = 6;
    Flags = PLATFORM_FLAGS;
    NumberOfFrames = PLATFORM_ANIMATION_NUM_FRAMES;
    Collision_Width = PLATFORM_COLLISION_WIDTH;
    Collision_Height = PLATFORM_COLLISION_HEIGHT;
    Collision_X = PLATFORM_COLLISION_X;
    Collision_Y = PLATFORM_COLLISION_Y;
    MaxSpeedX = PLATFORM_MAXSPEED_X;
    MaxSpeedY = PLATFORM_MAXSPEED_Y;
}

CPlatform::CPlatform(CEntity* temp, int params[])
{
    if (params[0] == UNINITIALIZED_PARAM)
        PlatformType = 1;
    else
        PlatformType = params[0];

    switch (PlatformType)
    {
        case 1:
            pWidth = PLATFORM1_WIDTH;
            pHeight = PLATFORM1_HEIGHT;
            pX = PLATFORM1_X;
            break;

        case 2:
            pWidth = PLATFORM2_WIDTH;
            pHeight = PLATFORM2_HEIGHT;
            pX = PLATFORM2_X;
            break;

        case 3:
            pWidth = PLATFORM3_WIDTH;
            pHeight = PLATFORM3_HEIGHT;
            pX = PLATFORM3_X;
            break;
    }

    // Offset Y by Height
    temp->Y -= pHeight;

    temp->Flags = PLATFORM_FLAGS;
    temp->Width = pWidth;
    temp->Height = pHeight;
    temp->NumberOfFrames = PLATFORM_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = PLATFORM_COLLISION_WIDTH;
    temp->Collision_Height = PLATFORM_COLLISION_HEIGHT;
    temp->Collision_X = PLATFORM_COLLISION_X;
    temp->Collision_Y = PLATFORM_COLLISION_Y;
    temp->MaxSpeedX = PLATFORM_MAXSPEED_X;
    temp->MaxSpeedY = PLATFORM_MAXSPEED_Y;

    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(PLATFORM_GFX));

    PopulateData(temp);
}

bool CPlatform::Load(std::string File, int Width, int Height, int NumberOfFrames)
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;

    return true;
}

void CPlatform::Render(SDL_Surface* SDisplay, int X2Offset)
{
    CEntity::Render(SDisplay, pX);
}

bool CPlatform::OnCollision(CEntity* Entity)
{
    SDL_Rect target = Entity->GetTargetBox();

    if (Below(Entity) &&
            target.x + target.w >= X && target.x <= X+Width)
    {
        // Player is on platform

        // Platform carries the player
        Carrying = Entity;
        Entity->CarriedBy = this;
    }

    return true;
}
