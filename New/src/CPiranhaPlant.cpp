
#include "CPiranhaPlant.h"
#include "GlobalFunctions.h"

void CPiranhaPlant::LoadSettings()
{
    CONST_ANIMATION_NUM_FRAMES = 4;
    
    CONST_POINTS_EARNED = 500;
    CONST_FLAGS = 9;
    CONST_WIDTH = 32;
    CONST_HEIGHT = 42;
    CONST_COLLISION_WIDTH = 0;
    CONST_COLLISION_HEIGHT = 0;
    CONST_COLLISION_X = 0;
    CONST_COLLISION_Y = 0;
    CONST_MAXSPEED_X = 0;
    CONST_MAXSPEED_Y = 16;
    CONST_GFX = "./gfx/piranhaplant.png";

    HasSecondState = false;
    JumpTime = SDL_GetTicks();
}

CPiranhaPlant::CPiranhaPlant()
{
    LoadSettings();
}

CPiranhaPlant::CPiranhaPlant(CEntity* temp, int params[])
{   
    LoadSettings();
        
    CEnemy::Initialize(temp, params);
}

void CPiranhaPlant::Animate()
{
    CEntity::Animate();
}

void CPiranhaPlant::Loop()
{
    // Jump the plant every 3 seconds
    int CurrentTime = (SDL_GetTicks() - 3000);
    
    if (CurrentTime > JumpTime)
    {        
        JumpTime = SDL_GetTicks();
        Jump();        
    }
    
    CEntity::Loop();
}