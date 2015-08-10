#include "CGame.h"
#include <string>
#include "CAreaScoring.h"
#include "CDebugLogging.h"
#include "CStateManager.h"

CGame CGame::Instance;

CGame::CGame()
{
    CurrentLevel = 0;   
}

void CGame::Render() 
{
    if (CFramerate::FPSControl.Framerate_Control())
    {  
        SDL_Rect Rect;
        Rect.x = 0;
        Rect.y = 0;
        Rect.w = WINDOW_WIDTH;
        Rect.h = WINDOW_HEIGHT;

        // Print map to display
        CArea* CurrentArea = CLevel::Level.GetCurrentArea();

        // Clear display
        SDL_FillRect(SDisplay, &Rect, CurrentArea->GetBackgroundColour());

        CurrentArea->Render(SDisplay, -CCamera::Camera.GetX(), -CCamera::Camera.GetY());

        //Render each entity to display    
        for( size_t i = 0; i < CEntity::EntityList.size(); i++) 
        {
            if(!CEntity::EntityList[i]) continue;

            CEntity::EntityList[i]->Render(SDisplay);
        }

        CScreenFurniture::Furniture.Render(SDisplay);

        //Flip to screen
        SDL_Flip(SDisplay);
    }
}

void CGame::Tidy() 
{
    // Logging
    CDebugLogging::DebugLogging.Log("Game Closing - Tidying", 1); 
    
    CLevel::Level.Tidy();

    CurrentLevel = 0;
    
    // Remove all Entities from List
    int size = CEntity::EntityList.size();
    
    for(size_t i = 0; i < size; i++) 
    {
        if(!CEntity::EntityList[i])
                continue;

        CEntity::EntityList[i]->Tidy();
    }

    ClearEntities();
    
    // Close Debug Log if open
    CDebugLogging::DebugLogging.Tidy();
}

void CGame::Reset()
{    
    InitializeEntities();
    
    // If a Midway save point has been reached, restart from there
    if (CLevel::Level.MidwaySavePoint)
    {
        CLevel::Level.SetCurrentArea(CLevel::Level.MidwayGate->AreaID);
        CMario* player = GetPlayer();
        player->X = CLevel::Level.MidwayGate->X;
        player->Y = (CLevel::Level.MidwayGate->Y + CLevel::Level.MidwayGate->Height) - player->Height;        
    }else
        CLevel::Level.SetCurrentArea(0);
    
    // Start scoring & Timing
    CAreaScoring::AreaScoring.Init(true);
    
    CSoundManager::SoundManager.StopMusic();
    
    CDebugLogging::DebugLogging.Log("Game Reset", 1);    
}

CGame* CGame::GetInstance()
{
    return &Instance;
}

void CGame::NextLevel()
{
    CurrentLevel++;
    
    CLevel::Level.Load(Levels[CurrentLevel]);
    
    Reset();
}

void CGame::LevelComplete()
{        
    if (CurrentLevel + 1 >= Levels.size())
        GameComplete();
    else
    {
        NextLevel();
        
        // Switch States and Show Level Transition Screen
        CStateManager::SetAppState(STATE_LEVEL_TRANSITION, SDisplay, true);            
    }
}

int CGame::GetCurrentLevelByID()
{
    return CurrentLevel;
}

void CGame::GameOver()
{    
    CSoundManager::SoundManager.Play(FX_GAME_OVER);
    
    // Switch States and Show Level Transition Screen
    CStateManager::SetAppState(STATE_GAME_OVER, SDisplay);    
}

void CGame::GameComplete()
{    
    // Switch States and Show Level Transition Screen
    CStateManager::SetAppState(STATE_GAME_COMPLETE, SDisplay);    
}