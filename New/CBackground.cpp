#include "CBackground.h"
#include "Define.h"
#include "CArea.h"
#include "CLevel.h"

CBackground::CBackground()
{
    SBackground = NULL;  
    Animation.Oscillate = true;    
}

bool CBackground::Load(std::string File)
{
    char BackgroundFile[255];
    
    sscanf(File.c_str(), "%s %f %d %x\n", BackgroundFile, &BackgroundSpeed, &BackgroundFrames, &BackgroundColour);
    
    Animation.SetNumberOfFrames(BackgroundFrames);

    if ((SBackground = CSurface::Load(BackgroundFile)) == false)
        return false;    
    
    return true;
}

void CBackground::Loop()
{
    Animate();
}

void CBackground::Animate()
{
    Animation.Animate();
}

void CBackground::Render(SDL_Surface* SDisplay, int CameraX, int CameraY)
{    
    int X, Y;
    
    X = (int)(abs(CameraX) * BackgroundSpeed) % BACKGROUND_WIDTH;
    
    int AreaHeight = CLevel::Level.GetCurrentArea()->GetAreaHeight();
    int MapsTall = (AreaHeight / (MAP_HEIGHT * TILE_SIZE)) - 1;
    
    Y = (CameraY + (AreaHeight * MapsTall)) - (AreaHeight - WINDOW_HEIGHT);
    
    CSurface::Draw(SDisplay, SBackground, 
                        0, Y,   // DEST
                        X, Animation.GetCurrentFrame() * BACKGROUND_HEIGHT, //SRC
                        WINDOW_WIDTH, BACKGROUND_HEIGHT); // SIZE
    
    // Fill any remaining screen space
    int BackgroundFilled = BACKGROUND_WIDTH - X;
    
    if (BackgroundFilled < WINDOW_WIDTH) // There's a gap at edge of screen
    {
        int GapSize = WINDOW_WIDTH - BackgroundFilled;
        
        // Fill the gap
        CSurface::Draw(SDisplay, SBackground, 
                                WINDOW_WIDTH - GapSize, Y,   // DEST
                                0, Animation.GetCurrentFrame() * BACKGROUND_HEIGHT, //SRC
                                GapSize, BACKGROUND_HEIGHT); // SIZE        
    }

}

void CBackground::Tidy()
{   
    if (SBackground)
        SDL_FreeSurface(SBackground); 
    
    SBackground = NULL;
}