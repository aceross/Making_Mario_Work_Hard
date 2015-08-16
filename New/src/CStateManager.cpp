#include "../include/CStateManager.h"
#include "../include/CDebugLogging.h"

#include "../include/CSplash.h"
#include "../include/CGame.h"
#include "../include/CLevelTransition.h"
#include "../include/CGameOver.h"
#include "../include/CGameComplete.h"

CState* CStateManager::CurrentState = 0;
int     CStateManager::CurrentStateID = 0;

void CStateManager::OnEvent(SDL_Event* Event)
{
    if (CurrentState)
        CurrentState->OnEvent(Event);
}

void CStateManager::Loop()
{
    if (CurrentState)
        CurrentState->Loop();
}

void CStateManager::Render()
{
    if (CurrentState)
        CurrentState->Render();
}

void CStateManager::SetAppState(int AppStateID, SDL_Surface* SDisplay, bool MaintainCurrent, bool AlreadyActive)
{
    if (CurrentState && !MaintainCurrent)
        CurrentState->DeActivate();

    int Options[5] = {0};

    switch (AppStateID)
    {
        case STATE_SPLASH:
            CurrentState = CSplash::GetInstance();
            break;

        case STATE_GAME:
            CurrentState = CGame::GetInstance();
            break;

        case STATE_CREDITS:

            break;

        case STATE_LEVEL_TRANSITION:
            // Get Current Level
            if (CurrentStateID == STATE_GAME)
                Options[0] = ((CGame*)CurrentState)->GetCurrentLevelByID();

            CurrentState = CLevelTransition::GetInstance();
            break;

        case STATE_GAME_OVER:
            CurrentState = CGameOver::GetInstance();
            break;

        case STATE_GAME_COMPLETE:
            CurrentState = CGameComplete::GetInstance();
            break;
    }

    CurrentStateID = AppStateID;

    if (CurrentState && !AlreadyActive)
        CurrentState->Activate(SDisplay, Options);

    // Logging
    std::ostringstream Msg;
    Msg << "Game state switched to " << AppStateID;

    CDebugLogging::DebugLogging.Log(Msg.str(), 1);
}

CState* CStateManager::GetAppState()
{
    return CurrentState;
}
