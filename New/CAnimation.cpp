
#include "CAnimation.h"

CAnimation::CAnimation() 
{
    CurrentFrame    = 0; // Zero based value
    NumberOfFrames  = 0;
    FrameIncrement  = 1;
    FrameRate       = 100; //Milliseconds
    PreviousTime    = 0;
    Oscillate       = false;
    RunOnce         = false;
}

void CAnimation::Animate() 
{
    // No Animation if only 1 frame
    if (NumberOfFrames <= 1)
    {
        CurrentFrame = 0;
        return;
    }
    
    if(PreviousTime + FrameRate > SDL_GetTicks())
        return;
 
    PreviousTime = SDL_GetTicks();

    CurrentFrame += FrameIncrement;
    
    if(Oscillate) 
    {
        if(FrameIncrement > 0) 
        {
            if(CurrentFrame >= NumberOfFrames - 1)
                FrameIncrement = -FrameIncrement;
            
        }else
        {
            if(CurrentFrame <= 0)
                FrameIncrement = -FrameIncrement;
        }
    } else
    {
        if(CurrentFrame >= NumberOfFrames)
        {
            if (RunOnce)
            {
                CurrentFrame = NumberOfFrames - 1;
                AnimationComplete = true;
            }
            else
            {
                AnimationComplete = false;
                CurrentFrame = 0;
            }
        }
    }
}

void CAnimation::SetFrameRate(int Rate) 
{
    FrameRate = Rate;
}


void CAnimation::SetCurrentFrame(int Frame) 
{
    if(Frame < 0 || Frame >= NumberOfFrames) return;

    CurrentFrame = Frame;
}


int CAnimation::GetCurrentFrame() 
{
    return CurrentFrame;
}

void CAnimation::SetNumberOfFrames(int Frames)
{
    NumberOfFrames = Frames;
}
