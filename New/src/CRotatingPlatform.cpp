#include "CRotatingPlatform.h"
#include <cmath>
#include "CLevel.h"

CRotatingPlatform::CRotatingPlatform()
{
    Radius = 100;
    RotationSpeed = 20;
    CurrentAngle = 0;
    Flags = RP_FLAGS;
    MoveTime = 0;
    Stopped = true;
}

void CRotatingPlatform::Initialize(int params[])
{
    /*
     * Params
     * 
     * 0. Platform Type
     * 1. Start Angle
     * 2. End Angle
     * 3. Direction
     * 4. Oscillate 
     */
    
    StartAngle = params[1] * RP_DEGREE_FRACTIONS;
    EndAngle = params[2] * RP_DEGREE_FRACTIONS;
    Direction = params[3];
    
    Stopped = true;
    
    if (params[4] == 1)
        Oscillate = true;
    else
        Oscillate = false;
    
    CurrentAngle = StartAngle;
    Radius = RP_NUM_OF_SPOKES * RP_SPOKE_SIZE + (RP_SPOKE_SIZE / 2);
    RotationSpeed = RP_ROTATIONSPEED;
    
    Flags = RP_FLAGS;
    
    OriginX = X;
    OriginY = Y;

    // set initial platform co-ordinates
    FindNewPosition();

    MoveTime = 0;
    
    SSpoke = CSurfaceManager::SurfaceManager.GetSurface(RP_SPOKE_GFX);
    SBlock = CSurfaceManager::SurfaceManager.GetSurface(RP_BLOCK_GFX);  
}


void CRotatingPlatform::Render(SDL_Surface* SDisplay, int X2Offset)
{   
    // Only if in current area
    if (CLevel::Level.GetCurrentAreaID() != AreaID)
        return;
    
    // Draw Central Block
    if(SBlock == NULL || SDisplay == NULL) return;

    CSurface::Draw( SDisplay, SBlock, 
                    (OriginX - (RP_SPOKE_SIZE / 2)) - CCamera::Camera.GetX(), 
                    (OriginY - (RP_SPOKE_SIZE / 2)) - CCamera::Camera.GetY(), 
                    0, 0, RP_SPOKE_SIZE, RP_SPOKE_SIZE);
    
    // Render Spokes
    for (int x=0; x < RP_NUM_OF_SPOKES; x++)
        CSurface::Draw( SDisplay, SSpoke, 
                        Spokes[x].X - CCamera::Camera.GetX(), 
                        Spokes[x].Y - CCamera::Camera.GetY(), 
                        0, 0, RP_SPOKE_SIZE, RP_SPOKE_SIZE);    
    
    
    CPlatform::Render(SDisplay, X2Offset);
}


void CRotatingPlatform::Loop()
{
    // Move platform around origin in 1 degree increments
    // One move every RotationSpeed ms
    
    if (Stopped)
        return;
    
    int CurrentTime = (SDL_GetTicks() - RotationSpeed);
    
    if (CurrentTime > MoveTime)       
    {                
        MoveTime = SDL_GetTicks();      

        FindNewPosition();
        
        if ((Oscillate) && ((CurrentAngle == EndAngle) || (CurrentAngle == StartAngle)))
            Direction *= -1;        
    }    
    
    CPlatform::Loop();
}

float CRotatingPlatform::X_at_Radius(int radius, int angle)
{
    return OriginX + radius * cos(( (angle/RP_DEGREE_FRACTIONS) * M_PI) / 180);
}

float CRotatingPlatform::Y_at_Radius(int radius, int angle)
{
    return OriginY + radius * sin(( (angle/RP_DEGREE_FRACTIONS) * M_PI) / 180);
}

bool CRotatingPlatform::OnCollision(CEntity* Entity)
{
    if (Entity->Type == ENTITY_TYPE_PLAYER && Below(Entity))
        if (Stopped)
            Stopped = false;
    
    CPlatform::OnCollision(Entity);
}

void CRotatingPlatform::FindNewPosition()
{
    // Move the platform co-ordinates by 1/3 degree
    int NewAngle = (CurrentAngle + (1 * Direction)) % (360 * RP_DEGREE_FRACTIONS);
    NewAngle = (NewAngle < 0) ? NewAngle + (360 * RP_DEGREE_FRACTIONS) : NewAngle;

    // Get direction of platform
    float dX, dY, newX, newY;

    newX = X_at_Radius(Radius, NewAngle);
    newY = Y_at_Radius(Radius, NewAngle);

    float previousX = X;
    float previousY = Y;

    X = newX - (Width/2);
    Y = newY  - Height;

    dX = X - previousX;
    dY = Y - previousY;

    // Only move if no collisions
    if ( PositionValid( (int)(X + dX), (int)(Y + dY), true) )
    {
        // Move Everything
        CurrentAngle = NewAngle;

        // Update Spoke Positions
        for (int x=0; x < RP_NUM_OF_SPOKES; x++)
        {
            int SpokeRadius = (x + 1) * RP_SPOKE_SIZE;
            Spokes[x].X = X_at_Radius(SpokeRadius, CurrentAngle) - (RP_SPOKE_SIZE / 2);
            Spokes[x].Y = Y_at_Radius(SpokeRadius, CurrentAngle) - (RP_SPOKE_SIZE / 2);
        }

        if (Carrying)
        {
            // Move carried Item with platform
            Carrying->Y = Y - Carrying->Height;
            Carrying->X += dX;               
        }                        
    }
    else
    { 
        // put things back the way they were
        X = previousX;
        Y = previousY;
    }    
}