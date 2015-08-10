
#include "CApp.h"
#include "CDebugLogging.h"
#include "CSoundManager.h"
#include "CSurfaceManager.h"

#include <string>

/*
 Starting Point
 */
int main(int argc, char* argv[]) 
{
   
    CApp theApp;
    
    return theApp.Execute();
}

CApp::CApp() 
{
    SDisplay = NULL;
    Running = true;
}

bool CApp::Initialize()
{
    // SDL SETUP
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
    // Logging
    CDebugLogging::DebugLogging.Log("SDL Initialized", 1); 
        
    if((SDisplay = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
        return false;

    // Logging
    CDebugLogging::DebugLogging.Log("SDL Video Mode Set", 1); 

    // Load Fonts
    InitializeFonts();
    
    // Load Sounds
    CSoundManager::SoundManager.Initialize();
    
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    CStateManager::SetAppState(STATE_SPLASH, SDisplay);    
    
    return true;
}

int CApp::Execute() 
{   
    if(Initialize() == false)
        return -1;
    
    SDL_Event Event;

    while(Running) 
    {
        while(SDL_PollEvent(&Event))
            OnEvent(&Event);
        
        Loop();
        Render();
    }

    Tidy();

    return 0;
}

void CApp::Loop()
{    
    if (CFramerate::FPSControl.GameLoop_Control())
    {
        CStateManager::Loop();

        CFramerate::FPSControl.Loop();

        // Display FPS
        char Buffer[255];
        sprintf(Buffer, "%d", CFramerate::FPSControl.GetFPS());
        SDL_WM_SetCaption(Buffer, Buffer);
    }
}

void CApp::OnEvent(SDL_Event* Event) 
{
    // Events for the App itself
    CEvent::OnEvent(Event);
    
    // Pass event to the current app state
    CStateManager::OnEvent(Event);
}

void CApp::OnExit() 
{
    Running = false;
}

void CApp::Render() 
{
    CStateManager::Render();
    
    //Flip to screen
    SDL_Flip(SDisplay);
}

void CApp::Tidy() 
{
    // Deactivate running App State
    CStateManager::GetAppState()->DeActivate();
    
    // Free main SDL Surface
    SDL_FreeSurface(SDisplay);
    SDisplay = NULL;
    
    TidyFonts();
    
    CSoundManager::SoundManager.Tidy();
 
    CSurfaceManager::SurfaceManager.Tidy();
    
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
