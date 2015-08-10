#include "CPButton.h"
#include "GlobalFunctions.h"
#include "CQuestionBox.h"

CPButton::CPButton()
{
    Flags = PBUTTONFLAGS;
    Width = 0;
    Height = 0;
    NumberOfFrames = PBUTTONANIMATION_NUM_FRAMES;
    Collision_Width = PBUTTON_COLLISION_WIDTH;
    Collision_Height = PBUTTON_COLLISION_HEIGHT;
    Collision_X = PBUTTON_COLLISION_X;
    Collision_Y = PBUTTON_COLLISION_Y;    
    
    SecondState = false;
}

CPButton::CPButton(CEntity* temp, int params[])
{   
    // Offset Y by Height
    temp->Y -= PBUTTON_HEIGHT;    
    temp->Flags = PBUTTONFLAGS;
    temp->Width = PBUTTON_WIDTH;
    temp->Height = PBUTTON_HEIGHT;
    temp->NumberOfFrames = PBUTTONANIMATION_NUM_FRAMES;
    temp->Collision_Width = PBUTTON_COLLISION_WIDTH;
    temp->Collision_Height = PBUTTON_COLLISION_HEIGHT;
    temp->Collision_X = PBUTTON_COLLISION_X;
    temp->Collision_Y = PBUTTON_COLLISION_Y;
    temp->MaxSpeedX = PBUTTON_MAXSPEED_X;
    temp->MaxSpeedY = PBUTTON_MAXSPEED_Y;
    
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(PBUTTON_GFX));
    
    PopulateData(temp);
    
    SecondState = false;    
    Activated = false;
}

bool CPButton::Load(std::string File, int Width, int Height, int NumberOfFrames)
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;    
}

void CPButton::Loop()
{
    CurrentFrameCol = 0;
    
    if (SecondState)
        Animation.SetCurrentFrame(1);
    else
        Animation.SetCurrentFrame(0);
        
    CEntity::Loop();
}

void CPButton::Animate()
{
    
}

bool CPButton::OnCollision(CEntity* Entity)
{
    if (Entity->Type == ENTITY_TYPE_PLAYER && Below(Entity) && Activated == false)
    {
        Activated = true;
        SecondState = true;
        Collision_Y = PBUTTON_COLLISION_Y_SECONDSTATE;
        
        // Turn all coins in the area into blocks - points are scored & coins collected  
        int params[5] = {UNINITIALIZED_PARAM};
        
        for (int x=0, len=EntityList.size(); x < len; x++)
        {
            if (EntityList[x]->AreaID == AreaID && EntityList[x]->Type == ENTITY_TYPE_COIN)
            {
                int CoinX, CoinY, CoinHeight;
                CoinX = EntityList[x]->X;
                CoinY = EntityList[x]->Y;
                CoinHeight = EntityList[x]->Height;
                
                EntityList[x]->OnCollision(GetPlayer());
                
                // create used Question block in it's place
                CEntity block;
                
                int newID = block.ID;
                block.Type = ENTITY_TYPE_QUESTIONBOX;
                block.X = CoinX;
                block.Y = CoinY + CoinHeight;
                
                EntityList.push_back(new CQuestionBox(&block, params));                
                
                // Get new Block
                CEntity* newBlock = GetEntityByID(newID);
                
                if (newBlock)               
                    ((CQuestionBox*)newBlock)->Opened = true;
                                
            }
        }
        
    }
    
    CEntity::OnCollision(Entity);
}