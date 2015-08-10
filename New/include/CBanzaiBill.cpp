
#include "CBanzaiBill.h"
#include "GlobalFunctions.h"
#include "CSoundManager.h"

void CBanzaiBill::LoadSettings()
{
    CONST_ANIMATION_NUM_FRAMES = 1;
    CONST_LEFT_FRAMECOL = 0;
    CONST_RIGHT_FRAMECOL = 1;
    CONST_POINTS_EARNED = 500;
    CONST_FLAGS = 8;
    CONST_WIDTH = 128;
    CONST_HEIGHT = 128;
    CONST_COLLISION_WIDTH = 0;
    CONST_COLLISION_HEIGHT = 0;
    CONST_COLLISION_X = 0;
    CONST_COLLISION_Y = 0;
    CONST_MAXSPEED_X = 3;
    CONST_MAXSPEED_Y = 10;
    CONST_GFX = "./gfx/banzaibill.png";

    Paused = true;
    HasSecondState = false;
    DiesInSecondState = false;   
}

CBanzaiBill::CBanzaiBill()
{
    LoadSettings();
}

CBanzaiBill::CBanzaiBill(CEntity* temp, int params[])
{   
    LoadSettings();
    temp->ZIndex = 99;
    CEnemy::Initialize(temp, params);
}

void CBanzaiBill::Loop()
{   
    // Check if Mario is in range
    // In range = 1 screen's width away WINDOW_WIDTH
    
    if (Paused)
    {
        CMario* player = GetPlayer();

        if (player)
            if ( (X - player->X) <= WINDOW_WIDTH)
                Paused = false;
    }
    else
        CEnemy::Loop();
}

void CBanzaiBill::Kill()
{
    CSoundManager::SoundManager.Play(FX_STOMP);
    
    // Display Points
    ShowPoints(CONST_POINTS_EARNED, X, Y);
    // Add points to score
    CAreaScoring::AreaScoring.AddPoints(CONST_POINTS_EARNED); 
    
    // STOP!
    FollowPath = false;
    MoveLeft = MoveRight = false;
    
    // Jump Off Screen
    Flags = ENTITY_FLAG_GHOST | ENTITY_FLAG_GRAVITY;
    
    X -= 100;
    Y -= 100;
    
    SetInitialSpeed(5,5,0,0);
    
    CEntity::Kill();
}

