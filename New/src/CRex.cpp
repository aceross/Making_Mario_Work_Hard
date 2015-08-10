
#include "CRex.h"
#include "GlobalFunctions.h"

void CRex::LoadSettings()
{
    CONST_ANIMATION_NUM_FRAMES_SECONDSTATE = 3;
    CONST_ANIMATION_COL_SECONDSTATE = 2;
    CONST_ANIMATION_ROW_SECONDSTATE = 0;
    CONST_COLLISION_Y_SECONDSTATE = 45;
    CONST_SECONDSTATE_TIME_LIMIT = 15000;
    CONST_MAXSPEED_X_SECONDSTATE = 6;
    
    CONST_ANIMATION_NUM_FRAMES = 2;
    
    CONST_LEFT_FRAMECOL = 0;
    CONST_RIGHT_FRAMECOL = 1;
    
    CONST_POINTS_EARNED = 500;
    CONST_FLAGS = 1;
    CONST_WIDTH = 50;
    CONST_HEIGHT = 64;
    CONST_COLLISION_WIDTH = 0;
    CONST_COLLISION_HEIGHT = 0;
    CONST_COLLISION_X = 0;
    CONST_COLLISION_Y = 0;
    CONST_MAXSPEED_X = 2;
    CONST_MAXSPEED_Y = 12;
    CONST_GFX = "./gfx/rex.png";
    
    HasSecondState = true;
    DiesInSecondState = true;
}

CRex::CRex()
{
    LoadSettings();
}

CRex::CRex(CEntity* temp, int params[])
{   
    LoadSettings();
    
    CEnemy::Initialize(temp, params);
}

void CRex::Animate()
{
    if (SecondState)
        Animation.RunOnce = true;
    else
        Animation.RunOnce = false;
    
    CEnemy::Animate();
}