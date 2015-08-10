#include <unistd.h>

#include "CGateBar.h"
#include "GlobalFunctions.h"
#include "CLevel.h"
#include "CGame.h"
#include "CEventsManager.h"

CGateBar::CGateBar() 
{    
    ID = ++CEntity::EntityCounter;    
    Type = 17;
    
    FollowPath = false;
    LoopPath = false;    
    
    Flags = GATEBAR_FLAGS;
    NumberOfFrames = 0;
    Collision_Width = GATEBAR_COLLISION_WIDTH;
    Collision_Height = GATEBAR_COLLISION_HEIGHT;
    Collision_X = GATEBAR_COLLISION_X;
    Collision_Y = GATEBAR_COLLISION_Y;
    MaxSpeedX = GATEBAR_MAXSPEED_X;
    MaxSpeedY = GATEBAR_MAXSPEED_Y;   
    ZIndex = 2;
}

CGateBar::CGateBar(CGateBar* temp)
{               
    if (temp->Flags == 0) // Nothing passed so use default
        temp->Flags = GATEBAR_FLAGS;
    
    if (temp->GateType == GATE_TYPE_MIDWAY)
    {
        temp->Width = GATEBAR_MIDWAY_WIDTH;
        temp->Height = GATEBAR_MIDWAY_HEIGHT;
        Bar_Gfx = GATEBAR_MIDWAY_GFX;        
    }
    else if (temp->GateType == GATE_TYPE_GIANT)
    {
        temp->Width = GATEBAR_GIANT_WIDTH;
        temp->Height = GATEBAR_GIANT_HEIGHT;
        Bar_Gfx = GATEBAR_GIANT_GFX;     
        temp->FollowPath = true;
        temp->LoopPath = true;
        temp->PathIndex = 1;
    }

    temp->X = temp->ParentGate->X + (((temp->ParentGate->Width/3) * 2) - temp->Width);
    temp->Y = temp->ParentGate->Y + temp->ParentGate->Height - temp->Height;
    
    location temploc;
    
    // Bottom of gate
    temploc.X = temp->X;
    temploc.Y = temp->Y;        
    temp->Path.push_back(temploc);
    
    BottomY = temp->Y;
    
    // Top of gate
    temploc.X = temp->X;
    temploc.Y = temp->ParentGate->Y + (temp->ParentGate->SectionHeight * 2);        
    temp->Path.push_back(temploc);
    
    TopY = temploc.Y;
    
    temp->Collision_Width = GATEBAR_COLLISION_WIDTH;
    temp->Collision_Height = GATEBAR_COLLISION_HEIGHT;
    temp->Collision_X = GATEBAR_COLLISION_X;
    temp->Collision_Y = GATEBAR_COLLISION_Y;
    temp->MaxSpeedX = GATEBAR_MAXSPEED_X;
    temp->MaxSpeedY = GATEBAR_MAXSPEED_Y;

    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(Bar_Gfx));
    
    PopulateData(temp);
    
    GateType = temp->GateType;
    ParentGate = temp->ParentGate;
    PointsCollected = false;
    MidwayReached = false;
}

bool CGateBar::Load(std::string File, int Width, int Height, int NumberOfFrames)
{
    if(CEntity::Load(File, Width, Height, NumberOfFrames) == false) return false;
   
    return true;
}

bool CGateBar::OnCollision(CEntity* Entity) 
{
    if (GateType == GATE_TYPE_GIANT && Entity->Type == ENTITY_TYPE_PLAYER && !PointsCollected)
    {
        // score points depending on position of bar
        float MovementRange = BottomY - TopY;        
        float CurrentPosition = BottomY - Y;
        
        int Percentage = (CurrentPosition / MovementRange) * 100;
        
        int PointsScored = Percentage * 20;
        
        // Score and Display Points;
        CAreaScoring::AreaScoring.AddPoints(PointsScored);
        ShowPoints(PointsScored, X, Y);
        
        PointsCollected = true;    
        
        CSoundManager::SoundManager.Play(FX_COURSE_CLEAR);
        CSoundManager::SoundManager.PauseMusic();
        
        // Trigger SDL Custom Event after 2000ms delay
        CEventsManager::EventsManager.AddEvent(GAME_EVENT_LEVEL_COMPLETE, 2000);
             
    }
    
    if (GateType == GATE_TYPE_MIDWAY && Entity->Type == ENTITY_TYPE_PLAYER && !MidwayReached)
    {
        CLevel::Level.MidwaySavePoint = true;
        MidwayReached = true;
        
        // Move Bar to top
        FollowPath = true;
        LoopPath = false;
        Flags &= ~ENTITY_FLAG_GRAVITY;
        MinY = TopY - ParentGate->SectionHeight;
        
        CSoundManager::SoundManager.Play(FX_MIDWAY_GATE);
    }
    
    return true;
}
