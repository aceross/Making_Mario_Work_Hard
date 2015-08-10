#ifndef _CANIMATION_H_
    #define _CANIMATION_H_

#include <SDL.h>

class CAnimation 
{
    private:
        int             CurrentFrame;
        int             FrameIncrement;
        unsigned int    FrameRate; //Milliseconds - This is the FR of the animation NOT the over all game
        unsigned long   PreviousTime;

    public:
        int             NumberOfFrames;
        bool            Oscillate;
        bool            RunOnce;
        bool            AnimationComplete;
        
        CAnimation();

        void Animate();

        void SetFrameRate(int Rate);
        void SetNumberOfFrames(int Frames);
        void SetCurrentFrame(int Frame);
        int GetCurrentFrame();
        
};

#endif
