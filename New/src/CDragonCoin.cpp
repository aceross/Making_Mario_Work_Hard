#include <unistd.h>

#include "CDragonCoin.h"
#include "CAreaScoring.h"
#include "CLevel.h"

CDragonCoin::CDragonCoin(CEntity* temp, int params[])
{       
    // Offset Y by Height
    temp->Y -= DRAGONCOIN_HEIGHT;
    
    temp->Flags = DRAGONCOIN_FLAGS;
    temp->Width = DRAGONCOIN_WIDTH;
    temp->Height = DRAGONCOIN_HEIGHT;
    temp->NumberOfFrames = DRAGONCOIN_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = DRAGONCOIN_COLLISION_WIDTH;
    temp->Collision_Height = DRAGONCOIN_COLLISION_HEIGHT;
    temp->Collision_X = DRAGONCOIN_COLLISION_X;
    temp->Collision_Y = DRAGONCOIN_COLLISION_Y;
    temp->MaxSpeedX = DRAGONCOIN_MAXSPEED_X;
    temp->MaxSpeedY = DRAGONCOIN_MAXSPEED_Y;
    temp->Points = DRAGONCOIN_POINTS_EARNED;
    
    Animation.SetFrameRate(DRAGONCOIN_ANIMATION_FRAMERATE);
    
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(DRAGONCOIN_GFX));
    
    PopulateData(temp);
}

bool CDragonCoin::OnCollision(CEntity* Entity) 
{
    /* 
     * Dragon Coin specific rules
     * 
     * at least 5 per level - collect all 5 to get extra life
     * each one above 5 gives extra life
     */
    
    if ((Entity->Type == ENTITY_TYPE_PLAYER) && !Dead)
        CAreaScoring::AreaScoring.AddDragonCoin(1);
    
    CCoin::OnCollision(Entity);
}
