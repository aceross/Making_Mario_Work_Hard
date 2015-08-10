#include <unistd.h>

#include "CStretchBlock.h"
#include "CLevel.h"

CStretchBlock::CStretchBlock() 
{
    MoveTime = 0;
    PauseTime = 0;
}

CStretchBlock::CStretchBlock(CEntity* temp, int params[])
{   
    temp->Y -= STRETCHBLOCK_HEIGHT;
    
    temp->Flags = STRETCHBLOCK_FLAGS;
    temp->Width = STRETCHBLOCK_WIDTH * STRETCHBLOCK_NUM_OF_BLOCKS;
    temp->Height = STRETCHBLOCK_HEIGHT;
    temp->Collision_Width = STRETCHBLOCK_COLLISION_WIDTH;
    temp->Collision_Height = STRETCHBLOCK_COLLISION_HEIGHT;
    temp->Collision_X = STRETCHBLOCK_COLLISION_X;
    temp->Collision_Y = STRETCHBLOCK_COLLISION_Y;

    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(STRETCHBLOCK_GFX));
    
    PopulateData(temp);
    
    // Initialize Spoke Positions
    for (int x = 0; x < STRETCHBLOCK_NUM_OF_BLOCKS; x++) 
    {
        Blocks[x].X = X + (STRETCHBLOCK_WIDTH * x);            
        Blocks[x].Y = Y;
        Blocks[x].Stopped = false;
        Blocks[x].AtMiddle = false;
    }     
    
    MiddleBlock = STRETCHBLOCK_NUM_OF_BLOCKS / 2;
    
    Blocks[MiddleBlock].Stopped = true;
    Blocks[MiddleBlock].AtMiddle = true;
    
    Paused = false;
    Stopped = true;
    Direction = 1;
    MoveTime = 0;
    PauseTime = 0;
}

void CStretchBlock::Animate() 
{    
    CurrentFrameRow = 0;
    Animation.SetNumberOfFrames(0);
    
    CEntity::Animate();
}

void CStretchBlock::Render(SDL_Surface* SDisplay, int X2Offset)
{
    // Only if in current area
    if (CLevel::Level.GetCurrentAreaID() != AreaID)
        return;
    
    // Draw Blocks
    if(SEntity == NULL || SDisplay == NULL) return;
    
    if (CLevel::Level.showGrid)
    {
        // Display Target Box
        SDL_Rect rect = GetTargetBox();
        rect.x -= CCamera::Camera.GetX();
        rect.y -= CCamera::Camera.GetY();
        SDL_FillRect(SDisplay, &rect, 0xff0000);
    }
    
    for (int x=0; x < STRETCHBLOCK_NUM_OF_BLOCKS; x++)
        CSurface::Draw( SDisplay, SEntity, 
                        Blocks[x].X - CCamera::Camera.GetX(), 
                        Blocks[x].Y - CCamera::Camera.GetY(), 
                        0, 0, STRETCHBLOCK_WIDTH, STRETCHBLOCK_WIDTH);    
    
}

void CStretchBlock::Loop()
{
    if (Stopped)
        return;
    
    // Change Block positions
    // move 1px every STRETCHBLOCK_ANIM_SPEED ms
    
    if (Paused)
        if ((SDL_GetTicks() - STRETCHBLOCK_PAUSETIME) > PauseTime)
            Paused = false;
        else
            return;        
      
    int CurrentTime = (SDL_GetTicks() - STRETCHBLOCK_ANIM_SPEED);
    
    if (CurrentTime > MoveTime)       
    {    
        MoveTime = SDL_GetTicks();
        
        if (Direction == 1)
            ContractBlocks();
        else if (Direction == -1)
            ExpandBlocks();
        
        // Have all Blocks Stopped
        bool AllStopped = true;
        for (int x=0; x < STRETCHBLOCK_NUM_OF_BLOCKS; x++)
            if (Blocks[x].Stopped == false)
            {
                AllStopped = false;
                break;
            }
         
        if (AllStopped)
        {
            // Pause for 3 seconds
            Paused = true;
            PauseTime = SDL_GetTicks();
            
            Direction *= -1; // Switch Direction
            
            // Unlock the 1st and last block ready for expansion
            if (Direction == -1)
            {
                Blocks[0].Stopped = false;
                Blocks[STRETCHBLOCK_NUM_OF_BLOCKS - 1].Stopped = false;
            }
        }

    }
    
    CEntity::Loop();    
}

bool CStretchBlock::OnCollision(CEntity* Entity) 
{
    if (Entity->Type == ENTITY_TYPE_PLAYER && Below(Entity))
        if (Stopped)
            Stopped = false;
    
    return true;
}

void CStretchBlock::ContractBlocks()
{     
    for (int x=0; x < STRETCHBLOCK_NUM_OF_BLOCKS; x++)
    {
        // Ignore middle Block
        if (x == MiddleBlock)
            continue;

        if (Blocks[x].X == Blocks[MiddleBlock].X)
        {
            Blocks[x].Stopped = true;
            continue;
        }

        Blocks[x].Stopped = false;

        if (x < MiddleBlock) // Left Side
        {
            if (PositionValid((int)(X + 1), (int)(Y), true))
            {
                Blocks[x].X++;

                if (X + Collision_X + 1 <= Blocks[MiddleBlock].X)
                    Collision_X++;
            }
        }
        else if (x > MiddleBlock) // Right Side
        {
            if (PositionValid((int)(X - 1), (int)(Y), true))
            {
                Blocks[x].X--;

                if (X + Width - Collision_Width >= Blocks[MiddleBlock].X + STRETCHBLOCK_WIDTH)
                    Collision_Width++;
            }
        }            
    }       
}

void CStretchBlock::ExpandBlocks()
{
    for (int x=0; x < STRETCHBLOCK_NUM_OF_BLOCKS; x++)
    {
        if (Blocks[x].Stopped == true)
            continue;
        
        // Ignore middle Block
        if (x == MiddleBlock)
            continue;
        
        // Check if reached final destination
        if (Blocks[x].X == (X + (x * STRETCHBLOCK_WIDTH)))
        {
            Blocks[x].Stopped = true;
            continue;
        }

        if (x < MiddleBlock) // Left Side
        {        
            if (PositionValid((int)(X - 1), (int)(Y), true))
            {
                Blocks[x].X--;

                // Check if OK to release next blocks
                if ((Blocks[x].X <= Blocks[MiddleBlock].X - STRETCHBLOCK_WIDTH) && (x+1) != MiddleBlock)
                    Blocks[x+1].Stopped = false;

                if (Collision_X > 0 && x == 0)
                    Collision_X--;
            }
        }
        else if (x > MiddleBlock) // Right Side
        {
            if (PositionValid((int)(X + 1), (int)(Y), true))
            {
                Blocks[x].X++;

                // Check if OK to release next blocks
                if ((Blocks[x].X >= Blocks[MiddleBlock].X + STRETCHBLOCK_WIDTH) && (x-1) != MiddleBlock)
                    Blocks[x-1].Stopped = false;

                if (Collision_Width > 0 &&  x == STRETCHBLOCK_NUM_OF_BLOCKS-1)
                    Collision_Width--;
            }
        }            
    }           
}