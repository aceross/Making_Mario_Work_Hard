#include "CGameOver.h"
#include "CStateManager.h"

CGameOver CGameOver::Instance;

CGameOver::CGameOver()
{
    SMessage = NULL;    
}

bool CGameOver::Activate(SDL_Surface* SDisp, int Options[])
{ 
    SDisplay = SDisp;

    return true;
}

void CGameOver::DeActivate()
{
    if (SMessage)
    {
        SDL_FreeSurface(SMessage);
        SMessage = NULL;
    }
}

void CGameOver::Loop()
{
    
}

void CGameOver::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    // On any key press restart game
    CStateManager::SetAppState(STATE_LEVEL_TRANSITION, SDisplay);
}

void CGameOver::Render()
{
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WINDOW_WIDTH;
    Rect.h = WINDOW_HEIGHT;
    
    // Clear display
    SDL_FillRect(SDisplay, &Rect, 0);

    WriteText(SDisplay, "GAME OVER!", FontHuge, Yellow);   
    
    SDL_Flip(SDisplay);
}

CGameOver* CGameOver::GetInstance()
{
    return &Instance;
}


