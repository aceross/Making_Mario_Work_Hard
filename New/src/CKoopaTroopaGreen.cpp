
#include "CKoopaTroopaGreen.h"
#include "GlobalFunctions.h"

void CKoopaTroopaGreen::LoadSettings()
{
    CONST_ANIMATION_NUM_FRAMES_SECONDSTATE = 0;
    CONST_ANIMATION_COL_SECONDSTATE = 2;
    CONST_ANIMATION_ROW_SECONDSTATE = 0;
    CONST_COLLISION_Y_SECONDSTATE = 20;
    CONST_SECONDSTATE_TIME_LIMIT = 5000;
    CONST_MAXSPEED_X_SECONDSTATE = 0;
    
    CONST_ANIMATION_NUM_FRAMES = 2;
    
    CONST_LEFT_FRAMECOL = 0;
    CONST_RIGHT_FRAMECOL = 1;
    
    CONST_POINTS_EARNED = 500;
    CONST_FLAGS = 1;
    CONST_WIDTH = 52;
    CONST_HEIGHT = 52;
    CONST_COLLISION_WIDTH = 11;
    CONST_COLLISION_HEIGHT = 0;
    CONST_COLLISION_X = 11;
    CONST_COLLISION_Y = 0;
    CONST_MAXSPEED_X = 2;
    CONST_MAXSPEED_Y = 12;
    CONST_GFX = "./gfx/koopatroopagreen.png";
    
    HasSecondState = true;
    DiesInSecondState = false;
}

CKoopaTroopaGreen::CKoopaTroopaGreen()
{
    LoadSettings();
}

CKoopaTroopaGreen::CKoopaTroopaGreen(CEntity* temp, int params[])
{   
    LoadSettings();
    
    CEnemy::Initialize(temp, params);
}

void CKoopaTroopaGreen::GoSecondState(bool scorePoints)
{
    if (HasSecondState)
    {
        CanBeCarried = true;

        // STOP!
        FollowPath = false;
        AccelX = 0;
        SpeedX = 0;
        MoveLeft = MoveRight = false;
        
        CEnemy::GoSecondState(scorePoints);
    }
}

void CKoopaTroopaGreen::GoFirstState()
{   
    // continue movement
    if (Path.size() > 1)
        FollowPath = true;
    else
        FollowPath = false;
    
    SpeedX = SpeedY = 0;
    AccelX = AccelY = 0;
    
    CEnemy::GoFirstState();
}