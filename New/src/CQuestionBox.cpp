#include <unistd.h>

#include "CQuestionBox.h"

void CQuestionBox::LoadSettings()
{
    CONST_ANIMATION_FRAMERATE = 300;
    CONST_ANIMATION_NUM_FRAMES = 4;
    CONST_ANIMATION_NUM_FRAMES_OPENED = 0;

    CONST_ANIMATION_COL_OPENED = 1;
    CONST_ANIMATION_ROW_OPENED = 0;

    CONST_FLAGS = 1;
    CONST_WIDTH = 32;
    CONST_HEIGHT = 32;
    CONST_COLLISION_WIDTH = 0;
    CONST_COLLISION_HEIGHT = 0;
    CONST_COLLISION_X = 0;
    CONST_COLLISION_Y = 0;
    CONST_MAXSPEED_X = 0;
    CONST_MAXSPEED_Y = 5;
    CONST_GFX = "./gfx/questionbox.png";     
}

CQuestionBox::CQuestionBox() 
{   
    LoadSettings();
}

CQuestionBox::CQuestionBox(CEntity* temp, int params[])
{   
    LoadSettings();
    
    CBlock::Initialize(temp, params);
}
