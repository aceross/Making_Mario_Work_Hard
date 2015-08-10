#include "CGameComplete.h"
#include "CStateManager.h"

CGameComplete CGameComplete::Instance;

CGameComplete::CGameComplete()
{
    SMessage = NULL;    
}

bool CGameComplete::Activate(SDL_Surface* SDisp, int Options[])
{ 
    SDisplay = SDisp;

    return true;
}

void CGameComplete::DeActivate()
{
    if (SMessage)
    {
        SDL_FreeSurface(SMessage);
        SMessage = NULL;
    }
}

void CGameComplete::Loop()
{
    
}

void CGameComplete::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    // On any key press restart game
    CStateManager::SetAppState(STATE_LEVEL_TRANSITION, SDisplay,false,false);
}

void CGameComplete::Render()
{
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WINDOW_WIDTH;
    Rect.h = WINDOW_HEIGHT;
    
    // Clear display
    SDL_FillRect(SDisplay, &Rect, 0);

    WriteText(SDisplay, "YOU WIN!!", FontHuge, Yellow);   
    
    SDL_Flip(SDisplay);
}

CGameComplete* CGameComplete::GetInstance()
{
    return &Instance;
}



