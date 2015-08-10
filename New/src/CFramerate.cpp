#include "CFramerate.h"
#include <unistd.h>

CFramerate CFramerate::FPSControl;

CFramerate::CFramerate() 
{
    LastFrameTime = 0;
    LastLoopTime    = 0;

    SpeedFactor	= 0;

    Frames      = 0;
    FPS   = 0;

    FixFrameRate = true;
    FixGameLoop = true;
    
    Framerate_Control_StartTime = 0;
    GameLoop_Control_StartTime = 0;
}

void CFramerate::Loop() 
{
    if(LastFrameTime + 1000 < SDL_GetTicks()) 
    {
        LastFrameTime = SDL_GetTicks();
        FPS = Frames;
        Frames = 0;
    }
    
    // 32 is an arbitrary number. Change to alter the speed of the game
    SpeedFactor = ((SDL_GetTicks() - LastLoopTime) / 1000.0f) * 32.0f; 
    
    LastLoopTime = SDL_GetTicks();

    Frames++;
}

int CFramerate::GetFPS() 
{
    return FPS;
}

float CFramerate::GetSpeedFactor() 
{
    return SpeedFactor;
}

void CFramerate::Reset()
{
    LastFrameTime = 0;
    LastLoopTime    = SDL_GetTicks();

    SpeedFactor	= 0;

    Frames      = 0;
    FPS   = 0;
}

bool CFramerate::Framerate_Control()
{
    // For Fixed Frame rate control
    if (FixFrameRate)
    {
        int delay = ((Framerate_Control_StartTime + (1000 / FIXED_FRAMERATE)) - SDL_GetTicks());
        
        if (delay > 0)
            return false; //SDL_Delay(delay);
        else
        {
            Framerate_Control_StartTime = SDL_GetTicks();
            return true;
        }                
    } 
    else   
        return true;
}

bool CFramerate::GameLoop_Control()
{
    // For Fixed Frame rate control
    if (FixGameLoop)
    {
        int delay = ((GameLoop_Control_StartTime + (1000 / FIXED_GAMELOOP)) - SDL_GetTicks());
        
        if (delay > 0)
            return false; //SDL_Delay(delay);
        else
        {
            GameLoop_Control_StartTime = SDL_GetTicks();
            return true;
        }                
    } 
    else   
        return true;
}
