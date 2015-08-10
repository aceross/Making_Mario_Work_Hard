
#include "CCamera.h"
#include "CLevel.h"

CCamera CCamera::Camera;

CCamera::CCamera() 
{
    X = 0;
    Y = 0;

    TargetX = NULL;
    TargetY = NULL;

    TargetMode = TARGET_MODE_NORMAL;
}

// Moves camera by MoveX & MoveY
void CCamera::OnMove(int MoveX, int MoveY) 
{
	X += MoveX;
	Y += MoveY;
}

int CCamera::GetX() 
{
    if(TargetX != NULL) 
    {
        // Keep target in center of screen as much as possible
        if(TargetMode == TARGET_MODE_CENTER) 
        {                    
            float newX = *TargetX - (WINDOW_WIDTH / 2); 

            // Prevent being able to see beyond the map
            int areaWidth = CLevel::Level.GetCurrentArea()->GetAreaWidth() - WINDOW_WIDTH;
  
            if (newX < 0)
                newX = 0;
            else if (newX > areaWidth)
                newX = areaWidth;
            
            return newX;  
        }

        return *TargetX;
    }

    return X;
}


int CCamera::GetY() 
{
    if(TargetY != NULL) 
    {
        if(TargetMode == TARGET_MODE_CENTER) 
        {
            float newY = *TargetY - (WINDOW_HEIGHT / 2);

            // Prevent being able to see beyond the map
            int areaHeight = CLevel::Level.GetCurrentArea()->GetAreaHeight() - WINDOW_HEIGHT; 

            if (newY < 0)
                newY = 0;
            else if (newY > areaHeight)
                newY = areaHeight;

            return newY; 	
        }

        return *TargetY;
    }

    return Y;
}


void CCamera::SetPos(int X, int Y) 
{
    this->X = X;
    this->Y = Y;
}


void CCamera::SetTarget(float* X, float* Y) 
{
    TargetX = X;
    TargetY = Y;
}


