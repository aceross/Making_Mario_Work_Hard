#include <unistd.h>

#include "CRotatingBlock.h"
#include "CSoundManager.h"
#include "CBlockPiece.h"

void CRotatingBlock::LoadSettings()
{
    CONST_ANIMATION_FRAMERATE  =   200;
    CONST_ANIMATION_NUM_FRAMES  =          4;
    CONST_ANIMATION_NUM_FRAMES_OPENED  =   0;

    CONST_ANIMATION_COL_OPENED   =  1;
    CONST_ANIMATION_ROW_OPENED  =   0;

    CONST_FLAGS         =    1;
    CONST_WIDTH         =    32;
    CONST_HEIGHT         =   32;
    CONST_COLLISION_WIDTH  = 0;
    CONST_COLLISION_HEIGHT = 0;
    CONST_COLLISION_X      = 0;
    CONST_COLLISION_Y      = 0;
    CONST_MAXSPEED_X       = 0;
    CONST_MAXSPEED_Y       = 0;
    CONST_GFX    =  "./gfx/rotatingblock.png";     
}

CRotatingBlock::CRotatingBlock() 
{
    LoadSettings();
}

CRotatingBlock::CRotatingBlock(CEntity* temp, int params[])
{   
    LoadSettings();
    
    Rotating = false;
    
    CBlock::Initialize(temp, params);
}

void CRotatingBlock::Animate() 
{    
    if (Rotating)    
        Animation.SetNumberOfFrames(CONST_ANIMATION_NUM_FRAMES);    
    else
    {
        CurrentFrameRow = 0;
        Animation.SetNumberOfFrames(0);
    }
    
    CBlock::Animate();
}

void CRotatingBlock::Loop()
{
    if (Rotating)
        if (RotatingTime + ROTATION_TIME < SDL_GetTicks())
        {
            Rotating = false;
            Flags ^= ENTITY_FLAG_GHOST;
        }
    
    CBlock::Loop();
}

bool CRotatingBlock::OnCollision(CEntity* Entity) 
{
    // The box is a normal rotating block
    if ((!Opened) && (Entity->Type == ENTITY_TYPE_PLAYER) && (Above(Entity, true)) && !Contains)
    {
        Rotating = true;
        RotatingTime = SDL_GetTicks();
        
        Flags |= ENTITY_FLAG_GHOST;
        CSoundManager::SoundManager.Play(FX_BREAK_BLOCK);
        
        return true;
    }
   
    // Box Destroyed if Spun on from above
    if (Entity->Type == ENTITY_TYPE_PLAYER && Below(Entity, true))
    {
        if (((CMario*)Entity)->Spinning && ((CMario*)Entity)->MarioState >= SUPER_MARIO)
            BreakBlock();
    }
    
    CBlock::OnCollision(Entity);
    
    return true;
}

void CRotatingBlock::Kill()
{
    DeathDelay = 0;
    CEntity::Kill();
}

void CRotatingBlock::BreakBlock()
{
    // Destroy block
    Kill();
    
    // Show pieces
    CreateBlockPiece(X + 8, Y - 40, -10, -8);
    CreateBlockPiece(X + 24, Y - 40, 10, -8);
    CreateBlockPiece(X + 8, Y - 16, -8, -8);
    CreateBlockPiece(X + 24, Y - 16, 8, -8);
}

void CRotatingBlock::CreateBlockPiece(int x, int y, int sX, int sY)
{
    CBlockPiece piece;

    piece.X = x;
    piece.Y = y;

    piece.SetInitialSpeed(sX, sY, 0 , 0);

    location temploc;
    temploc.X = piece.X;
    temploc.Y = piece.Y;        
    piece.Path.push_back(temploc);

    CEntity::EntityList.push_back(new CBlockPiece(&piece, NULL));  
}