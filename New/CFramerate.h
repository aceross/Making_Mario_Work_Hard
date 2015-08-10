#ifndef _CFRAMERATE_H_
    #define _CFRAMERATE_H_

#include <SDL.h>
#include "Define.h"

#define FIXED_FRAMERATE 30
#define FIXED_GAMELOOP  120

class CFramerate 
{
    public:
        static          CFramerate FPSControl;

    private:
        unsigned int    LastFrameTime;
        int             LastLoopTime;
        float           SpeedFactor;
        int		FPS;
        int             Frames;
        
        bool            FixFrameRate;
        bool            FixGameLoop;
        
        unsigned int    Framerate_Control_StartTime;
        unsigned int    GameLoop_Control_StartTime;
    public:
        CFramerate();
        
        void            Loop();
        
        void            Reset();
        
        int             GetFPS();
        float           GetSpeedFactor();        
        
        bool            Framerate_Control();
        bool            GameLoop_Control();
};


#endif
