#include "CMario.h"
#include "CDebugLogging.h"
#include "CLevel.h"
#include "CPowerUp.h"
#include "Define_HUD.h"
#include "CEventsManager.h"
#include "CSoundManager.h"

CMario::CMario() 
{    
    ID = ++CEntity::EntityCounter;
    
    Animation.Oscillate = true;
    
    CarryOffsetX = 30;
    CarryOffsetY = -30;

    Flags = MARIO_FLAGS;
    Width = MARIO_WIDTH;
    Height = MARIO_HEIGHT;
    NumberOfFrames = MARIO_ANIMATION_NUM_FRAMES;
    Collision_Width = MARIO_COLLISION_WIDTH;
    Collision_Height = MARIO_COLLISION_HEIGHT;
    Collision_X = MARIO_COLLISION_X;
    Collision_Y = MARIO_COLLISION_Y;
    MaxSpeedX = MARIO_MAXSPEED_X;
    MaxSpeedY = MARIO_MAXSPEED_Y;
    OnBeanStalk = NULL;
    InPipe = NULL;
    ZIndex = MARIO_ZINDEX;
    Ducking = false;
    Spinning = false;
    FlashingTime = 0;
    Hidden = false;
    CurrentPowerUp = 0;
    ReservePowerUp = 0;

    ChangeMarioState(NORMAL_MARIO);
}

CMario::CMario(CEntity* temp, int params[])
{   
    // Offset Y by Height
    temp->Y -= MARIO_HEIGHT;
    
    temp->CarryOffsetX = 30;
    temp->CarryOffsetY = -30;    
    temp->Flags = MARIO_FLAGS;
    temp->Width = MARIO_WIDTH;
    temp->Height = MARIO_HEIGHT;
    temp->NumberOfFrames = MARIO_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = MARIO_COLLISION_WIDTH;
    temp->Collision_Height = MARIO_COLLISION_HEIGHT;
    temp->Collision_X = MARIO_COLLISION_X;
    temp->Collision_Y = MARIO_COLLISION_Y;
    temp->MaxSpeedX = MARIO_MAXSPEED_X;
    temp->MaxSpeedY = MARIO_MAXSPEED_Y;
    temp->ZIndex = MARIO_ZINDEX;
    
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(MARIO_GFX));
    
    PopulateData(temp);
    
    OnBeanStalk = NULL;
    InPipe = NULL;
    Ducking = false;
    Spinning = false;
    FlashingTime = 0;
    Hidden = false;
    CurrentPowerUp = 0;
    ReservePowerUp = 0;
    
    SpinTime = SDL_GetTicks();
    
    ChangeMarioState(NORMAL_MARIO);
}

bool CMario::Load(char* File, int Width, int Height, int NumberOfFrames) 
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

void CMario::Loop() 
{       
    // If Mario is dead then reset the game
    if (Dead)                  
        if ((SDL_GetTicks() - DeathTime) >= DeathDelay)
            CEventsManager::EventsManager.AddEvent(GAME_EVENT_RESET);           
        
    SDL_Rect target = GetTargetBox();
    
    // Don't let Player walk off edge of map
    AtLeftEdge = ((target.x < 0) && MoveLeft) ? true : false;
    AtRightEdge = ((target.x >= CLevel::Level.GetCurrentArea()->GetAreaWidth() - target.w) && MoveRight) ? true : false;
    
    // If Mario Falls Off bottom of Map - KILL!!!
    if (Y > CCamera::Camera.GetY() + WINDOW_HEIGHT + 200) // +200 so that Mario doesn't jump back onto screen when dead
        CAreaScoring::AreaScoring.AddLife(-1);
    
    // CHECK: Still being carried?
    if (CarriedBy)
    {                
        if (!Collides(CarriedBy->X, CarriedBy->Y - 3, CarriedBy->Width, CarriedBy->Height))
        {             
            // (Y-3) due to movement of platform
            CarriedBy->Carrying = NULL;  // Cancel carry
            CarriedBy = NULL;
        }            
    }

    // CHECK: Still on BeanStalk?
    if (OnBeanStalk)
    {
        if (!Collides(OnBeanStalk->X+15, OnBeanStalk->Y, 5, OnBeanStalk->Height))
        {            
            OnBeanStalk = NULL;
            Flags = MARIO_FLAGS;
            AccelY = 0;
            SpeedY = 0;
        }  
    }
    
    // CHECK: Still in Pipe?
    if (InPipe)
    {
        if (!Collides(InPipe->X+15, InPipe->Y-1, 5, InPipe->Height))
        {            
            InPipe = NULL;
            Flags = MARIO_FLAGS;
        }  
    }

    // Flashing
    if (FlashingTime)
    {
        static int FlashCount = 15;
        
        if (FlashingTime + 100 < SDL_GetTicks()) 
        {
            FlashingTime = SDL_GetTicks();
            FlashCount--;
            Hidden = (Hidden) ? false : true;
        }
        
        if (FlashCount < 0) // Stop flashing and reset counters
        {
            Hidden = false;
            FlashingTime = 0;
            FlashCount = 15;
        }
    }
    
    CEntity::Loop();
}

void CMario::Render(SDL_Surface* SDisplay) 
{
    if (!Hidden)
        CEntity::Render(SDisplay);
}


void CMario::Tidy() 
{
    CEntity::Tidy();
}


void CMario::Animate() 
{   
    Animation.SetFrameRate(MARIO_FRAMERATE);
    
    if(OnBeanStalk)
    {
        CurrentFrameCol = Animation_Col_Climb;        
        Animation.SetCurrentFrame(0);
        Animation.SetNumberOfFrames(MARIO_ANIMATION_NUM_FRAMES_CLIMB);      
    }else if (Ducking)
    {        
        if (FaceLeft)
            CurrentFrameCol = Animation_Col_Duck;
        else if (FaceRight)
            CurrentFrameCol = Animation_Col_Duck + 1;
        
        Animation.SetCurrentFrame(0);
        Animation.SetNumberOfFrames(MARIO_ANIMATION_NUM_FRAMES_DUCK);
            
    }
    else if (Spinning)
    {
        CurrentFrameCol = Animation_Col_Spin;     
        Animation.SetFrameRate(MARIO_FRAMERATE_SPIN);
        Animation.SetNumberOfFrames(MARIO_ANIMATION_NUM_FRAMES_SPIN);        
    }    
    else if ((int)SpeedY == 0) // We're on the floor
    {       
        // If we're jumping set the animation columns back to normal position
        // Set direction of animation
        if (FaceLeft)
            CurrentFrameCol = Animation_Col_Norm;
        else if (FaceRight)
            CurrentFrameCol = Animation_Col_Norm + 1;
        
        if(SpeedX != 0)
            Animation.NumberOfFrames = Animation_NumFrames; // walking
        else
            Animation.NumberOfFrames = 0; // not moving so stop animation   

    }
    else // we're jumping / falling
    {     
        if (!CarriedBy)
        {
            Animation.NumberOfFrames = MARIO_ANIMATION_NUM_FRAMES_JUMP;
            Animation.SetCurrentFrame(0);

            // If we're standing set the animation columns to jumping
            if (CurrentFrameCol == Animation_Col_Norm)
                CurrentFrameCol = Animation_Col_Jump;
            else if (CurrentFrameCol == Animation_Col_Norm + 1)
                CurrentFrameCol = Animation_Col_Jump + 1;

            // Set direction of animation if moving
            if(MoveLeft)        CurrentFrameCol = Animation_Col_Jump;
            else if(MoveRight)  CurrentFrameCol = Animation_Col_Jump + 1;
        }
    }
    
    CEntity::Animate();
}


bool CMario::OnCollision(CEntity* Entity) 
{
    
    return true;
}

void CMario::Kill()
{
    MoveLeft = MoveRight = false;
    
    // Jump Off Screen
    Flags = ENTITY_FLAG_GHOST | ENTITY_FLAG_GRAVITY;
    
    X += 40;
    Y -= 40;
    
    SetInitialSpeed(5,5,0,0);
    
    CSoundManager::SoundManager.PauseMusic();
    CSoundManager::SoundManager.Play(FX_LOSE_LIFE);
    
    CEntity::Kill();      
}

void CMario::Duck(bool duck)
{
    if (duck) // Duck down
    {
        Ducking = true;
        MoveLeft = false;
        MoveRight = false;
        Collision_Y = CollisionY_Duck;        
    }else // stand up
    {
        Ducking = false;
        Collision_Y = (MarioState == NORMAL_MARIO) ? MARIO_COLLISION_Y : SUPER_MARIO_COLLISION_Y;        
    }
}

void CMario::Spin(bool Spin)
{
    Spinning = Spin;
    
    // Play Sound only every 1 secs
    int CurrentTime = (SDL_GetTicks() - 1000);
    
    if (CurrentTime > SpinTime)
    {        
        SpinTime = SDL_GetTicks();
        CSoundManager::SoundManager.Play(FX_SPIN);        
    }
    
}

void CMario::ChangeMarioState(int state)
{   
    int OriginalMarioState = (MarioState) ? MarioState : NORMAL_MARIO;
    
    MarioState = state;
    
    switch (state)
    {
        case NORMAL_MARIO:   
            Animation_Col_Norm = MARIO_ANIMATION_COL_NORM;
            Animation_Col_Jump = MARIO_ANIMATION_COL_JUMP;
            Animation_Col_Climb = MARIO_ANIMATION_COL_CLIMB;
            Animation_Col_Duck = MARIO_ANIMATION_COL_DUCK;
            Animation_Col_Spin = MARIO_ANIMATION_COL_SPIN;
            Animation_NumFrames = MARIO_ANIMATION_NUM_FRAMES;
            CollisionY_Duck = MARIO_COLLISION_Y_DUCK;           
            Animation.SetNumberOfFrames(MARIO_ANIMATION_NUM_FRAMES);
            Collision_Width = MARIO_COLLISION_WIDTH;
            Collision_X = MARIO_COLLISION_X;
            Collision_Y = MARIO_COLLISION_Y;
            
            // Change all powerups back to defaults
            for (int x = 0, len = EntityList.size(); x < len; x++)
                if (EntityList[x]->Type == ENTITY_TYPE_POWERUP)                    
                    ((CPowerUp*)EntityList[x])->ChangePowerUpType(((CPowerUp*)EntityList[x])->OriginalPowerupType);

            if (state < OriginalMarioState) // Power Down
            {
                DropReservePowerup();
                CurrentPowerUp = 0;
                ReservePowerUp = 0;
            }
            
            break;

        case SUPER_MARIO:     
            Animation_Col_Norm = SUPER_MARIO_ANIMATION_COL_NORM;
            Animation_Col_Jump = SUPER_MARIO_ANIMATION_COL_JUMP;
            Animation_Col_Climb = SUPER_MARIO_ANIMATION_COL_CLIMB;
            Animation_Col_Duck = SUPER_MARIO_ANIMATION_COL_DUCK;
            Animation_Col_Spin = SUPER_MARIO_ANIMATION_COL_SPIN;
            Animation_NumFrames = SUPER_MARIO_ANIMATION_NUM_FRAMES;
            CollisionY_Duck = SUPER_MARIO_COLLISION_Y_DUCK;           
            Animation.SetNumberOfFrames(SUPER_MARIO_ANIMATION_NUM_FRAMES);
            Collision_Width = SUPER_MARIO_COLLISION_WIDTH;
            Collision_X = SUPER_MARIO_COLLISION_X;
            Collision_Y = SUPER_MARIO_COLLISION_Y;  
            
            // Change all Red Mushrooms (SUPER_MARIO) to Fire Flowers
            for (int x = 0, len = EntityList.size(); x < len; x++)
                if (EntityList[x]->Type == ENTITY_TYPE_POWERUP)
                    if ( ((CPowerUp*)EntityList[x])->OriginalPowerupType == POWERUP_TYPE_RED)
                        ((CPowerUp*)EntityList[x])->ChangePowerUpType(POWERUP_TYPE_FIREFLOWER);
            
            if (state < OriginalMarioState) // Power Down
            {
                DropReservePowerup();
                CurrentPowerUp = ReservePowerUp;
                ReservePowerUp = 0;
            }
            if (state > OriginalMarioState) // Power Up
            {
                CurrentPowerUp = POWERUP_TYPE_RED;                
            }
            
            // Play Sound
            CSoundManager::SoundManager.Play(FX_POWERUP);
    
            break;

        case FIRE_MARIO:     
            Animation_Col_Norm = FIRE_MARIO_ANIMATION_COL_NORM;
            Animation_Col_Jump = FIRE_MARIO_ANIMATION_COL_JUMP;
            Animation_Col_Climb = FIRE_MARIO_ANIMATION_COL_CLIMB;
            Animation_Col_Duck = FIRE_MARIO_ANIMATION_COL_DUCK;
            Animation_Col_Spin = FIRE_MARIO_ANIMATION_COL_SPIN;
            Animation_NumFrames = FIRE_MARIO_ANIMATION_NUM_FRAMES;
            CollisionY_Duck = FIRE_MARIO_COLLISION_Y_DUCK;           
            Animation.SetNumberOfFrames(FIRE_MARIO_ANIMATION_NUM_FRAMES);
            Collision_Width = FIRE_MARIO_COLLISION_WIDTH;
            Collision_X = FIRE_MARIO_COLLISION_X;
            Collision_Y = FIRE_MARIO_COLLISION_Y;          

            if (state > OriginalMarioState) // Power Up
            {
                if (!ReservePowerUp)
                    ReservePowerUp = CurrentPowerUp;
                
                CurrentPowerUp = POWERUP_TYPE_FIREFLOWER;                
            }
            
            // Play Sound
            CSoundManager::SoundManager.Play(FX_POWERUP);
    
            break;            
    }    
}

void CMario::ThrowFireball()
{
    // Only launch 1 fireball every 0.5 seconds
    static int LaunchTime;
    int CurrentTime = (SDL_GetTicks() - 500);
    
    if (CurrentTime > LaunchTime)       
        LaunchTime = SDL_GetTicks();      
    else
        return;
    
    CFireball fireball;

    fireball.ThrownBy = this;
    
    fireball.Y = Y + 40;
    
    if (FaceLeft)
    {
        fireball.X = X - 10;
        fireball.SetInitialSpeed(-MaxSpeedX, 0, 0 , 0);        
        fireball.MoveLeft = true;
        fireball.MoveRight = false;        
    }else if (FaceRight)
    {
        fireball.X = X + Width + 1;
        fireball.SetInitialSpeed(MaxSpeedX, 0, 0 , 0);   
        fireball.MoveLeft = false;
        fireball.MoveRight = true;        
    }
   
    fireball.LifeSpan = 2000;
    
    location temploc;
    temploc.X = fireball.X;
    temploc.Y = fireball.Y;        
    fireball.Path.push_back(temploc);

    CEntity::EntityList.push_back(new CFireball(&fireball, NULL)); 
    
    // Play Sound
    CSoundManager::SoundManager.Play(FX_FIREBALL);
}

void CMario::DropReservePowerup()
{
    if (ReservePowerUp)
    {
        CPowerUp powerup;
        
        powerup.X = CCamera::Camera.GetX() + POWERUP_X;
        powerup.Y = CCamera::Camera.GetY() + POWERUP_Y + POWERUPS_WH;

        powerup.SDisplay = SDisplay;
        
        int params[1];
        params[0] = ReservePowerUp;
        
        location temploc;
        temploc.X = powerup.X;
        temploc.Y = powerup.Y; 
        
        powerup.MaxSpeedX = 0;
        powerup.Path.push_back(temploc);

        CEntity::EntityList.push_back(new CPowerUp(&powerup, params)); 
        
        // Play Sound
        CSoundManager::SoundManager.Play(FX_RESERVE_RELEASED);
    }
}

void CMario::SwitchPowerUp()
{
    if (ReservePowerUp)
    {
        int OrigPowerUp = CurrentPowerUp;

        ChangeMarioState(NORMAL_MARIO);

        ReservePowerUp = OrigPowerUp;   
    }
}