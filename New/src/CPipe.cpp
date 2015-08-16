#include <unistd.h>

#include "../include/CPipe.h"
#include "../include/GlobalFunctions.h"
#include "../include/CLevel.h"
#include "../include/CSoundManager.h"

CPipe::CPipe()
{
    ID = ++CEntity::EntityCounter;

    Flags = PIPE_FLAGS;
    Width = PIPE_WIDTH;
    Height = 50;
    NumberOfFrames = PIPE_ANIMATION_NUM_FRAMES;
    Collision_Width = PIPE_COLLISION_WIDTH;
    Collision_Height = PIPE_COLLISION_HEIGHT;
    Collision_X = PIPE_COLLISION_X;
    Collision_Y = PIPE_COLLISION_Y;
    MaxSpeedX = PIPE_MAXSPEED_X;
    MaxSpeedY = PIPE_MAXSPEED_Y;

    Direction = 0;
    Colour = 0;
    Destination = 0;
}

CPipe::CPipe(CEntity* temp, int params[])
{

    // parameter 0: Height
    // parameter 1: Direction 0=up 1=down
    // parameter 2: type/colour 0=blue 1=yellow 2=red 3=green
    // parameter 3: destination - ID of pipe to link to

    if (params[0] != UNINITIALIZED_PARAM)
        temp->Height = params[0];

    if (params[1] != UNINITIALIZED_PARAM)
        Direction = params[1];

    if (params[2] != UNINITIALIZED_PARAM)
        Colour = params[2];

    if (params[3] != UNINITIALIZED_PARAM)
        Destination = params[3];

    // Offset Y by Height
    temp->Y -= temp->Height;
    temp->Flags = PIPE_FLAGS;
    temp->Width = PIPE_WIDTH;
    temp->NumberOfFrames = PIPE_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = PIPE_COLLISION_WIDTH;
    temp->Collision_Height = PIPE_COLLISION_HEIGHT;
    temp->Collision_X = PIPE_COLLISION_X;
    temp->Collision_Y = PIPE_COLLISION_Y;
    temp->MaxSpeedX = PIPE_MAXSPEED_X;
    temp->MaxSpeedY = PIPE_MAXSPEED_Y;

    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(PIPE_GFX));

    PopulateData(temp);

    ZIndex = 101;
}

bool CPipe::Load(char* File, int Width, int Height, int NumberOfFrames)
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;

    return true;
}

void CPipe::Loop()
{

    CEntity::Loop();
}

void CPipe::Render(SDL_Surface* SDisplay, int X2Offset)
{
    // Only if in current area
    if (CLevel::Level.GetCurrentAreaID() != AreaID)
        return;

    if(SEntity == NULL || SDisplay == NULL) return;

    int ColY;

    if (Direction == 0)
        ColY = 0;
    else
        ColY = SEntity->h - Height;

    CSurface::Draw( SDisplay,
                    SEntity,
                    X - CCamera::Camera.GetX(),
                    Y - CCamera::Camera.GetY(),
                    Colour * Width,
                    ColY,
                    Width, Height);
}


void CPipe::Tidy()
{
    CEntity::Tidy();
}


void CPipe::Animate()
{
    CEntity::Animate();
}


bool CPipe::OnCollision(CEntity* Entity)
{
    if (Entity->Type == ENTITY_TYPE_PLAYER && Below(Entity))
    {
        Entity->InPipe = this;
    }

    return true;
}

void CPipe::Transport(CEntity* Entity)
{
    // transport Entity to Destination
    if (Destination)
    {
        CPipe* destPipe = (CPipe*)GetEntityByID(Destination);

        if (destPipe)
        {
            CSoundManager::SoundManager.Play(FX_PIPE);

            Entity->AreaID = destPipe->AreaID;

            Entity->X = destPipe->X + 1;

            if (destPipe->Direction == 0)
                Entity->Y = destPipe->Y - Entity->Height - 10;
            else
                Entity->Y = destPipe->Y + destPipe->Height;

            // Switch Area
            CLevel::Level.SetCurrentArea(destPipe->AreaID);
        }

    }
}
