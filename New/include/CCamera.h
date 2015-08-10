
#ifndef _CCAMERA_H_
    #define _CCAMERA_H_

#include <SDL.h>
#include "Define.h"
#include "CArea.h"

enum 
{
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera 
{
    public:
        static CCamera Camera;
        int TargetMode; 
        
    private:
        int X;
        int Y;

        float* TargetX;
        float* TargetY;

    public:
        CCamera();
        
        void OnMove(int MoveX, int MoveY);
        
        int GetX();
        int GetY();
        void SetPos(int X, int Y);
        void SetTarget(float* X, float* Y);
};

#endif
