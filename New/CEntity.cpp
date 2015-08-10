#include "CEntity.h"
#include "CKoopaTroopaGreen.h"
#include "CDebugLogging.h"
#include "CLevel.h"
#include "CSoundManager.h"
#include "GlobalFunctions.h"


std::vector<CEntity*> 	CEntity::EntityList;
int CEntity::EntityCounter;

CEntity::CEntity() 
{
    ID = ++EntityCounter;
    
    SEntity = NULL;

    AreaID = CLevel::Level.GetCurrentAreaID();
    
    X = 0;
    Y = 0;

    PathIndex = 0;
    FollowPath = false;
    LoopPath = false;
    LoopInc = 1;
    
    Width 	= 0;
    Height 	= 0;

    MoveLeft = MoveRight = false;
    FaceLeft = FaceRight = false;
    MoveUp = MoveDown = false;
    
    AtLeftEdge = false;
    AtRightEdge = false;

    Type = 	ENTITY_TYPE_GENERIC;

    Dead = false;
    Flags = 0;

    SpeedX = 0;
    SpeedY = 0;

    AccelX = 0;
    AccelY = 0;

    MaxSpeedX = 10;
    MaxSpeedY = 12;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

    Collision_X = 0;
    Collision_Y = 0;

    Collision_Width  = 0;
    Collision_Height = 0;

    CanJump = false;
    
    Slope_Offset_X = Slope_Offset_Y = 0;
    
    MinX = MinY = MaxX = MaxY = 0;
    
    CreationTime = SDL_GetTicks();
    
    LifeSpan = 0;
    
    Carrying = CarriedBy = NULL;
    CanBeCarried = false;
    CanCarry = false;
    Thrown = false;
    CarryOffsetX = CarryOffsetY = 0;
    
    OnBeanStalk = NULL;
    InPipe = NULL;
    Ducking = false;
    ZIndex = 0;
    DeathDelay = 3000;
    Killable = false;        
}

CEntity::~CEntity() 
{

}

bool CEntity::Load(std::string File, int Width, int Height, int NumberOfFrames) 
{
    
    return true;
}

void CEntity::SetSurface(SDL_Surface* surface)
{
    SEntity = surface;
}

void CEntity::Loop() 
{       
    // Only if in current area
    if (CLevel::Level.GetCurrentAreaID() != AreaID)
        return;
    
    // Check for Death!!
    if (Dead)
    {
        if ((SDL_GetTicks() - DeathTime) >= DeathDelay)
            RemoveFromList();
    } 
    else if (LifeSpan) // Check Lifespan 
        if ((SDL_GetTicks() - CreationTime) >= LifeSpan)
            Kill();
      
    // Check for Path following
    if (FollowPath)
    {
        MoveRight = (X < Path.at(PathIndex).X) ? true : false;
        MoveLeft =  (X > Path.at(PathIndex).X) ? true : false; 
        
        MoveDown = (Y < (Path.at(PathIndex).Y - Height)) ? true : false;
        MoveUp =  ((int)Y > ((int)Path.at(PathIndex).Y - Height)) ? true : false; 

        FaceLeft = MoveLeft;
        FaceRight = MoveRight;        
    }
    
    // Check for carrying something
    if (Carrying)
    {        
        int Multiplier = (FaceRight) ? 1 : -1;

        if (CarryOffsetX) Carrying->X = X + (CarryOffsetX * Multiplier);
        
        if (CarryOffsetY) Carrying->Y = Y + CarryOffsetY;         
     }
   
    //We're not Moving
    if(MoveLeft == false && MoveRight == false && MoveUp == false && MoveDown == false)
        StopMove();
   
    if(Flags & ENTITY_FLAG_GRAVITY) AccelY = 0.75f;
    
    if(MoveLeft)        AccelX = -0.5;
    else if(MoveRight)  AccelX = 0.5;

    if(MoveUp)         AccelY = -0.75f;
    else if(MoveDown)  AccelY = 0.75f;
    
    if (OnBeanStalk)
    {
        if (!MoveDown && !MoveUp)
        {
            AccelY  = 0;
            SpeedY = 0;
        }
    }
    
    // Check if we are on a slope
    /*
    if (OnSlope())
        printf("we are ON a slope\n");
    else
        printf("we are NOT ON a slope\n");
    */
    
    SpeedX += AccelX * CFramerate::FPSControl.GetSpeedFactor();
    SpeedY += AccelY * CFramerate::FPSControl.GetSpeedFactor();
    
    if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
    if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
    if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
    if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

    if (AtLeftEdge || AtRightEdge)
    {
        SpeedX = 0;
        AccelX = 0;
    }
    
    if (MaxY) // a maxY value has been set
    {
        if (Y > MaxY)
        {
            Y = MaxY;
            SpeedY = 0;
            AccelY = 0;
        }
    }

    if (MinY) // a MinY value has been set
    {
        if (Y < MinY)
        {
            Y = MinY;
            SpeedY = 0;
            AccelY = 0;
        }
    }
    
    Animate();
    
    Move(SpeedX, SpeedY);    
}

void CEntity::Render(SDL_Surface* SDisplay, int X2Offset) 
{
    // Only if in current area
    if (CLevel::Level.GetCurrentAreaID() != AreaID)
        return;

    if(SEntity == NULL || SDisplay == NULL) return;
    
    if (CLevel::Level.showGrid)
    {
        // Display Target Box
        SDL_Rect rect = GetTargetBox();
        rect.x -= CCamera::Camera.GetX();
        rect.y -= CCamera::Camera.GetY();
        SDL_FillRect(SDisplay, &rect, 0xff0000);
    }
    
    CSurface::Draw( SDisplay, 
                    SEntity, 
                    X - CCamera::Camera.GetX(), 
                    Y - CCamera::Camera.GetY(), 
                    (CurrentFrameCol * Width) + X2Offset, 
                    (CurrentFrameRow + Animation.GetCurrentFrame()) * Height, 
                    Width, Height);
    
}

void CEntity::Tidy() 
{    
    SEntity = NULL;
}

void CEntity::Animate() 
{
    Animation.Animate();
}

bool CEntity::OnCollision(CEntity* Entity) 
{        
    // Player has tried to pick up a carry-able object.
    // Add it to the Player      
    if ((Entity->Type == ENTITY_TYPE_PLAYER) && (Entity->CanCarry == true) && (CanBeCarried == true))
    {
        Entity->Carrying = this;
        CarriedBy = Entity;
    }
    
    return true;
}

/*
 * Move Entity by MoveX, MoveY pixels
 * The move is done in tiny increments determined by the speed factor
 * rather than in one large move to MoveX, MoveY
 */ 
void CEntity::Move(float MoveX, float MoveY) 
{       
    if (MoveX == 0 && MoveY == 0) return; // We've stopped
   
    CanJump = false; // We don't yet know if we can jump
    
    float speedfactor = CFramerate::FPSControl.GetSpeedFactor();
   
    MoveX *= speedfactor;
    MoveY *= speedfactor;
 
    //Store the step increment in each direction
    double NewX = 0;
    double NewY = 0; 
    
    if (MoveX != 0) NewX = (MoveX >= 0) ? speedfactor : -speedfactor; // for going left or right
    if (MoveY != 0) NewY = (MoveY >= 0) ? speedfactor : -speedfactor; // for going up or down
     
    while(true)
    {     
        if(Flags & ENTITY_FLAG_GHOST) // Can pass through everything
        {
            PositionValid((int)(X + NewX), (int)(Y + NewY)); //We don't care about collisions, but we need to send events to other entities

            X += NewX;
            Y += NewY;
        } 
        else // Check for Collisions in X & Y direction
        {
            if (OnSlope())
            {
                
                if ( PositionValid((int)(X + NewX), (int)(Y)), true )
                    X += NewX;
                else
                    SpeedX = 0;
                
                if ( PositionValid( (int)(X), (int)(Y + NewY)), true )
                    Y += NewY + Slope_Offset_Y;
                
                CanJump = true;
                SpeedY = 0;
                 
            }else
            {                
                // Can we move in X
                if ( PositionValid((int)(X + NewX), (int)(Y)) )
                {  
                    X += NewX;
                            
                    if (Carrying)
                        Carrying->X += NewX;                           
                }else
                    SpeedX = 0;
                
                // Can we move in Y                
                if ( PositionValid( (int)(X), (int)(Y + NewY)) )
                {
                    Y += NewY;
                    
                    // It's a platform (or similar) with something on it
                    if (Carrying && (MoveUp || MoveDown))
                        Carrying->Y = Y - Carrying->Height;                                      
                }
                else // We are on the floor
                {
                    CanJump = true;
                    SpeedY = 0;
                }
                 
            }
           
        } 
              
        // Check Path Following
        PathFollowing();

        // Reduce MoveX, MoveY by the step increment
        MoveX += -NewX;
        MoveY += -NewY;
     
        // Check for over-run
        if(NewX > 0 && MoveX <= 0) NewX = 0;
        if(NewX < 0 && MoveX >= 0) NewX = 0;
        
        if(NewY > 0 && MoveY <= 0) NewY = 0;
        if(NewY < 0 && MoveY >= 0) NewY = 0;
        
        if(MoveX == 0) NewX = 0;
        if(MoveY == 0) NewY = 0;
        
        // Check if we're finished
        if(MoveX == 0 && MoveY == 0) break;        
        if(NewX  == 0 && NewY == 0) break;
    }
   
}

void CEntity::StopMove() 
{
    if(SpeedX > 0) AccelX = -1;
    
    if(SpeedX < 0) AccelX =  1;
    
    // We're going slowly enough so stop
    if(SpeedX < 2.0f && SpeedX > -2.0f) 
    {
        AccelX = 0;
        SpeedX = 0;
    }
}

bool CEntity::Collides(int objectX, int objectY, int objectW, int objectH) 
{
    int left1, left2, right1, right2, top1, top2, bottom1, bottom2;

    SDL_Rect target = GetTargetBox();

    left1 = target.x;
    right1 = left1 + target.w - 1;
    top1 = target.y;
    bottom1 = top1 + target.h - 1;
    
    left2 = objectX;
    right2 = objectX + objectW- 1;
    top2 = objectY;
    bottom2 = objectY + objectH - 1;

    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

bool CEntity::PositionValid(int NewX, int NewY, bool EntityOnly) 
{       
    if (!EntityOnly)
    {
        // Check Map Collision

        // Get the new Target box location
        SDL_Rect target = GetTargetBox(NewX, NewY);

        // Get location measured in Tiles (NOT pixels)
        // This gets all the tiles that the Entity will occupy
        int StartTileX      = target.x / TILE_SIZE;
        int StartTileY      = target.y / TILE_SIZE;
        int EndTileX        = (target.x + target.w - 1) / TILE_SIZE;
        int EndTileY        = (target.y + target.h - 1) / TILE_SIZE;

        for ( int y = StartTileY; y <= EndTileY; y++) 
            for ( int x = StartTileX; x <= EndTileX; x++) 
            {
                CTile* Tile = CLevel::Level.GetCurrentArea()->GetTile(x * TILE_SIZE, y * TILE_SIZE);

                if(PositionValid_Tile(Tile, x * TILE_SIZE, y * TILE_SIZE) == false) 
                    return false;             
            }
    }

    // Check Entity Collision
    if(!(Flags & ENTITY_FLAG_MAPONLY))
    {
        for (size_t i = 0; i < EntityList.size(); i++) 
        {
            // Only check against Entities in the same area
            if (AreaID != EntityList[i]->AreaID)
                continue;
            
            // Only check nearby objects i.e within 100px each way
            if (EntityList[i]->X < (X - 100) || EntityList[i]->X > (X+100))
                continue;

            if (Flags & ENTITY_FLAG_PLAYERONLY) // Only check collisions against player or fireballs
            {
                if (EntityList[i]->Type == ENTITY_TYPE_PLAYER || EntityList[i]->Type == ENTITY_TYPE_FIREBALL)
                    if(PositionValid_Entity(EntityList[i], NewX, NewY) == false) 
                        return false; 
                
            }else // Check All
            {
                // ignore if a playerOnly collision hits a non-player
                if (EntityList[i]->Flags & ENTITY_FLAG_PLAYERONLY && Type != ENTITY_TYPE_PLAYER)
                    continue;
                
                if(PositionValid_Entity(EntityList[i], NewX, NewY) == false) 
                    return false;     
            }          
        }        
    }

    return true;
}

bool CEntity::PositionValid_Tile(CTile* Tile, int X, int Y) 
{
    if (Tile == NULL) return true;

    if (Tile->TypeID == TILE_TYPE_BLOCK) return false;
    
    if ((Tile->TypeID == TILE_TYPE_BLOCK_ONEWAY) && Above(Y) ) return false;
  
    // SLOPES
    if ((Tile->TypeID == TILE_TYPE_SLOPE_0_15_LEFT) || (Tile->TypeID == TILE_TYPE_SLOPE_0_15_RIGHT))
    {
        Slope_Offset_X = 5;
        Slope_Offset_Y = -0.2;        
        return true;
    }
    
    return true;
}

bool CEntity::PositionValid_Entity(CEntity* Entity, int NewX, int NewY) 
{    
    // Only collide with Entities in the same area
    if (AreaID != Entity->AreaID)
        return true;
 
    // Get the new Target box location
    SDL_Rect target = GetTargetBox(NewX, NewY);   
   
    if (this != Entity && Entity != NULL && Entity->Dead == false && Carrying != Entity && 
            Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
            Entity->Collides(target.x, target.y, target.w, target.h) == true) 
    {
        // Collision Has Happened
        // Add it to list
        
        CEntityCollision EntityCol;

        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
       
        CEntityCollision::EntityCollisionList.push_back(EntityCol); 
        
        // Record Collision but allow progress if colliding with Ghost or Map Only
        if ((Entity->Flags & ENTITY_FLAG_GHOST) || (Entity->Flags & ENTITY_FLAG_MAPONLY))
            return true;        
        else
            return false;
    }

    return true;
}

bool CEntity::Jump() 
{   
    // Cancel any carrying
    // Allows entity to jump from moving platforms for instance
    if (CarriedBy)
    {       
        if ((CarriedBy->Type == ENTITY_TYPE_PLATFORM) || (CarriedBy->Type == ENTITY_TYPE_ROTATINGPLATFORM))
            CanJump = true; // Can always jump from platform
        
        CarriedBy->Carrying = NULL;  // Cancel carry
        CarriedBy = NULL;
    }
    
    if (CanJump == false) return false;    
    if (Ducking == true) return false;
    
    SpeedY = -MaxSpeedY;

    // Play Sound if Entity is on screen
    
    if (OnScreen(this))
        CSoundManager::SoundManager.Play(FX_JUMP);        
   
    return true;
}

void CEntity::Duck(bool duck)
{

}

bool CEntity::RemoveFromList()
{    
    std::vector<CEntity*>::iterator it = CEntity::EntityList.begin();
    
    for ( ; it != CEntity::EntityList.end(); ++it)
    {    
        if ((*it)->ID == this->ID)
        {               
            (*it)->Tidy();
            EntityList.erase(it);
            return true; 
        }
    }
    
    return false;
}

void CEntity::PopulateData(CEntity* temp)
{
    this->ID = temp->ID;
    this->AreaID = temp->AreaID;
    this->Type = temp->Type;
    this->Flags = temp->Flags;
    this->Width = temp->Width;
    this->Height = temp->Height;
    this->NumberOfFrames = temp->NumberOfFrames;
    this->Collision_X = temp->Collision_X;
    this->Collision_Y = temp->Collision_Y;
    this->Collision_Height = temp->Collision_Height;
    this->Collision_Width = temp->Collision_Width;
    this->MaxSpeedX = temp->MaxSpeedX;
    this->MaxSpeedY = temp->MaxSpeedY;
    this->X = temp->X;
    this->Y = temp->Y;
    this->FollowPath = temp->FollowPath;
    this->LoopPath = temp->LoopPath;
    this->Path = temp->Path;
    this->PathIndex = temp->PathIndex;
    this->Dead = false;
    this->MoveLeft = temp->MoveLeft;
    this->MoveRight = temp->MoveRight;    
    this->MoveUp = false;
    this->MoveDown = false;
    this->SDisplay = temp->SDisplay;

    this->SEntity = temp->SEntity;
    
    Animation.NumberOfFrames = this->NumberOfFrames;
    
    this->MaxY = temp->MaxY;
    this->MinY = temp->MinY;
    this->MaxX = temp->MaxX;
    this->MinX = temp->MinX;
    this->SpeedX = temp->SpeedX;
    this->SpeedY = temp->SpeedY;
    this->AccelX = temp->AccelX;
    this->AccelY = temp->AccelY;
    this->LifeSpan = temp->LifeSpan;    
    this->CarryOffsetX = temp->CarryOffsetX;
    this->CarryOffsetY = temp->CarryOffsetY;  
    this->OnBeanStalk = temp->OnBeanStalk;    
    this->ZIndex = temp->ZIndex;
    this->Points = temp->Points;
}

bool CEntity::Above(int Y)
{    
    SDL_Rect target = GetTargetBox();
    
    if ( (int)(target.y + target.h) <= Y) 
        return true;
    else
        return false;
}

bool CEntity::Above(CEntity* entity, bool Directly)
{
    SDL_Rect tThis = GetTargetBox();
    SDL_Rect tEntity  = entity->GetTargetBox();
    
    if ( (int)(tThis.y + tThis.h - 1) <= (int)tEntity.y)    
    {
        if (Directly && (tEntity.x > tThis.x + tThis.w - 5 || tEntity.x + tEntity.w < tThis.x + 5))
            return false;
        else
            return true;        
    }else
        return false;
}

bool CEntity::Below(int Y)
{
    if ( (int)(this->Y) <= Y) 
        return false;
    else
        return true;
}

bool CEntity::Below(CEntity* entity, bool Directly)
{
    SDL_Rect target_this = GetTargetBox();
    SDL_Rect target_entity  = entity->GetTargetBox();
    
    if ( (int)(target_this.y) >= (int)target_entity.y + target_entity.h)
    {
        if (Directly && (target_entity.x > target_this.x + target_this.w - 5 || target_entity.x + target_entity.w < target_this.x + 5))
            return false;
        else
            return true;        
    }else
        return false;
    
}

bool CEntity::OnSlope()
{
    CTile* tile = CLevel::Level.GetCurrentArea()->GetTile( (X+Collision_X) + ((Width-Collision_Width)/2), Y+Height-1);
    
    if (tile == NULL)
        return false;
    
    if ((tile->TypeID == TILE_TYPE_SLOPE_0_15_LEFT) || (tile->TypeID == TILE_TYPE_SLOPE_0_15_RIGHT) )
        return true;
    else
        return false;    
}

SDL_Rect CEntity::GetTargetBox()
{
    SDL_Rect target;
    
    target.x = X + Collision_X;
    target.y = Y + Collision_Y;
    target.w = Width - Collision_X - Collision_Width;
    target.h = Height - Collision_Y - Collision_Height;
    
    return target;
}

// Get Target box when at position X,Y
SDL_Rect CEntity::GetTargetBox(int X, int Y)
{
    SDL_Rect target;
    
    target.x = X + Collision_X;
    target.y = Y + Collision_Y;
    target.w = Width - Collision_X - Collision_Width;
    target.h = Height - Collision_Y - Collision_Height;
    
    return target;
}

void CEntity::PathFollowing()
{
    // Check Path Location        
    if (FollowPath)
    {                                    
        if ( ((int)X == (int)Path.at(PathIndex).X) && ((int)Y == ((int)Path.at(PathIndex).Y - Height) ) ) // We're reached the wanted point       
            PathIndex += LoopInc; // move to next point
        
        if (LoopPath) // Follow loop forever
        {
            if (LoopInc > 0)
            {
                if (PathIndex >= Path.size()-1) // We've reached the end of the path
                    LoopInc = -LoopInc;                                           
            } 
            else
                if (PathIndex <= 0)
                    LoopInc = -LoopInc;                            
        }
        else // Follow the path just once
            if (PathIndex > Path.size()-1) // We've reached the end of the path
            {
                PathIndex = Path.size()-1;
                FollowPath = false;  // cancel path following
                MoveLeft = MoveRight = false; // cancel movement
                MoveUp = MoveDown = false;
            }           
    }
}

void CEntity::SetInitialSpeed(float sX, float sY, float aX, float aY)
{
    SpeedX = sX;
    SpeedY = sY;
    AccelX = aX;
    AccelY = aY;
}

void CEntity::Throw()
{
    Carrying->Thrown = true;

    if (FaceRight)
    {
        Carrying->X = X + Width + 20;                    
        Carrying->SetInitialSpeed(20,0,10,0);
        Carrying->MaxSpeedX = 30;   
        Carrying->MoveLeft = false;
        Carrying->MoveRight = true;
    }else
    {
        Carrying->X = X - Carrying->Width - 20;                    
        Carrying->SetInitialSpeed(-20,0,-10,0);
        Carrying->MaxSpeedX = 30;  
        Carrying->MoveRight = false;
        Carrying->MoveLeft = true;
    }    

    Carrying->CarriedBy = NULL;    
    
    CSoundManager::SoundManager.Play(FX_THROW);
}

void CEntity::Drop()
{
    Carrying->Thrown = false;
    Carrying->MoveRight = false;
    Carrying->MoveLeft = false;

    if (FaceRight)
        Carrying->X = X + Width;                  
    else
        Carrying->X = X - Carrying->Width;   
        
    Carrying->CarriedBy = NULL;
    Carrying = NULL;
    CanCarry = false;
}

void CEntity::Kill()
{    
    Dead = true;
    DeathTime = SDL_GetTicks();
}

bool CEntity::isDead()
{
    return Dead;
}