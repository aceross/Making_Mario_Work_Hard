#include "../include/CSplash.h"
#include "../include/CStateManager.h"

CSplash CSplash::Instance;

CSplash::CSplash()
{
    SSplash = NULL;
}

bool CSplash::Activate(SDL_Surface* SDisp, int Options[])
{
    SDisplay = SDisp;

    SSplash = CSurface::Load("./gfx/splash.png");

    SplashStartTime = SDL_GetTicks();

    return true;
}

void CSplash::DeActivate()
{
    if (SSplash)
    {
        SDL_FreeSurface(SSplash);
        SSplash = NULL;
    }

}

void CSplash::Loop()
{
    if (SplashStartTime + 2000 < SDL_GetTicks())
        CStateManager::SetAppState(STATE_LEVEL_TRANSITION,SDisplay);

        //CStateManager::SetAppState(STATE_GAME,SDisplay);
}

void CSplash::Render()
{
    if (SSplash)
        CSurface::Draw(SDisplay, SSplash, 0, 0);

}

CSplash* CSplash::GetInstance()
{
    return &Instance;
}
