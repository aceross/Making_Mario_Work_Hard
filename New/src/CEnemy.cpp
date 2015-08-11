
#include "../include/CEnemy.h"
#include "../include/GlobalFunctions.h"
#include "../include/CSoundManager.h"

CEnemy::CEnemy()
{
    Flags = CONST_FLAGS;
    Width = CONST_WIDTH;
    Height = CONST_HEIGHT;
    NumberOfFrames = CONST_ANIMATION_NUM_FRAMES;
    Collision_Width = CONST_COLLISION_WIDTH;
    Collision_Height = CONST_COLLISION_HEIGHT;
    Collision_X = CONST_COLLISION_X;
    Collision_Y = CONST_COLLISION_Y;
    MaxSpeedX = CONST_MAXSPEED_X;
    MaxSpeedY = CONST_MAXSPEED_Y;
    Killable = true;
}

void CEnemy::Initialize(CEntity* temp, int params[])
{
    // Offset Y by Height
    temp->Y -= CONST_HEIGHT;

    temp->Flags = CONST_FLAGS;
    temp->Width = CONST_WIDTH;
    temp->Height = CONST_HEIGHT;
    temp->NumberOfFrames = CONST_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = CONST_COLLISION_WIDTH;
    temp->Collision_Height = CONST_COLLISION_HEIGHT;
    temp->Collision_X = CONST_COLLISION_X;
    temp->Collision_Y = CONST_COLLISION_Y;
    temp->MaxSpeedX = CONST_MAXSPEED_X;
    temp->MaxSpeedY = CONST_MAXSPEED_Y;

    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(CONST_GFX));

    PopulateData(temp);

    SecondState = false;
    SecondStateTime = 0;
    Killable = true;
}

bool CEnemy::Load(char* File, int Width, int Height, int NumberOfFrames)
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;

    return true;
}

void CEnemy::Loop()
{
    //printf("X:%f SF:%f\n",X,CFramerate::FPSControl.GetSpeedFactor());

    // Stay in SecondState for CONST_SECONDSTATE_TIME_LIMIT ms
    if (SecondState)
    {
        unsigned int currTime = SDL_GetTicks();

        if ((currTime - SecondStateTime) >= CONST_SECONDSTATE_TIME_LIMIT)
            GoFirstState();
    }

    CEntity::Loop();
}

void CEnemy::Tidy()
{
    CEntity::Tidy();
}


void CEnemy::Animate()
{
    if (SecondState)
    {
        Animation.NumberOfFrames = CONST_ANIMATION_NUM_FRAMES_SECONDSTATE;

    }else
    {
        if((int)SpeedX != 0)
            Animation.NumberOfFrames = CONST_ANIMATION_NUM_FRAMES;
        else
            Animation.NumberOfFrames = 0;

        if(MoveLeft)        CurrentFrameCol = CONST_LEFT_FRAMECOL;
        else if(MoveRight)  CurrentFrameCol = CONST_RIGHT_FRAMECOL;
    }

    CEntity::Animate();
}


bool CEnemy::OnCollision(CEntity* Entity)
{
    // ignore collisions if dead
    if (Dead)
        return false;

    // collision with player
    if ((Entity->Type == ENTITY_TYPE_PLAYER && !SecondState) || (Entity->Type != ENTITY_TYPE_PLAYER && Entity->Thrown == true && !SecondState) )
    {
        bool dies = false;
        bool besecondstate = false;

        // enemy only dies if player is above; else player dies
        if (Entity->Above(this))
            if (HasSecondState) // Switch to SecondState if one exists
                besecondstate = true;
            else
                dies = true;

        // enemy dies if hit anywhere if object has been thrown at them
        if (Entity->Thrown) dies = true;

        // enemy only dies if player is above; else player dies
        if (dies)
            Kill();
        else if (besecondstate)
            GoSecondState();
        else
            CAreaScoring::AreaScoring.AddLife(-1);
    }
    else if (Entity->Type == ENTITY_TYPE_PLAYER && SecondState && DiesInSecondState) // it's been hit by player in an already squashed state
    {
        // enemy only dies if player is above; else player dies
        if (Entity->Above(this))
            Kill();
        else
            CAreaScoring::AreaScoring.AddLife(-1);
    }

    CEntity::OnCollision(Entity);

    return true;
}

/*
 * Displays Points & switches animation to 2nd state
 */
void CEnemy::GoSecondState(bool scorePoints)
{
    if (HasSecondState)
    {
        // Display Points
        if (scorePoints)
        {
            ShowPoints(CONST_POINTS_EARNED, X, Y);
            CAreaScoring::AreaScoring.AddPoints(CONST_POINTS_EARNED);
        }

        SecondState = true;
        SecondStateTime = SDL_GetTicks();

        SpeedX = CONST_MAXSPEED_X_SECONDSTATE;

        // Change Animation
        CurrentFrameCol = CONST_ANIMATION_COL_SECONDSTATE;
        CurrentFrameRow = CONST_ANIMATION_ROW_SECONDSTATE;
        Animation.NumberOfFrames = CONST_ANIMATION_NUM_FRAMES_SECONDSTATE;

        // Change Target Box to make it smaller
        Collision_Y = CONST_COLLISION_Y_SECONDSTATE;

        CSoundManager::SoundManager.Play(FX_STOMP);
    }
}

void CEnemy::GoFirstState()
{
    SecondState = false;
    SecondStateTime = 0;

    // Cancel any carrying
    if (CarriedBy)
        CarriedBy->Drop();

    MaxSpeedX = CONST_MAXSPEED_X;
    MaxSpeedY = CONST_MAXSPEED_Y;

    // Change Animation
    CurrentFrameCol = 0;
    CurrentFrameRow = 0;
    Animation.NumberOfFrames = CONST_ANIMATION_NUM_FRAMES;

    // Change Target Box to make it bigger
    Collision_Y = 0;
}

void CEnemy::Kill()
{
    CSoundManager::SoundManager.Play(FX_STOMP);

    MoveLeft = MoveRight = false;
    FollowPath = false;

    if (HasSecondState)
        GoSecondState(false);

    ShowPoints(CONST_POINTS_EARNED, X, Y);
    CAreaScoring::AreaScoring.AddPoints(CONST_POINTS_EARNED);

    // Jump Off Screen
    Flags = ENTITY_FLAG_GHOST | ENTITY_FLAG_GRAVITY;

    X += 40;
    Y -= 40;

    SetInitialSpeed(5,5,0,0);

    CEntity::Kill();
}
