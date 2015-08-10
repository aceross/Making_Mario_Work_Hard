/* 
 * File:   CBackground.h
 * Author: alan
 *
 * Created on January 29, 2013, 10:54 AM
 */

#ifndef CBACKGROUND_H
#define	CBACKGROUND_H

#include <string>
#include "CSurface.h"
#include "CAnimation.h"

#define BACKGROUND_WIDTH        1024
#define BACKGROUND_HEIGHT       860

class CBackground
{
    public:
        CBackground();
        
        bool    Load(std::string File);
        void    Render(SDL_Surface* SDisplay, int CameraX, int CameraY);
        void    Tidy();
        void    Animate();
        void    Loop();
        
        int     BackgroundColour;
        
    private:
        SDL_Surface*    SBackground;
        float           BackgroundSpeed;
        int             BackgroundFrames;
        
        CAnimation      Animation;      
};

#endif	/* CBACKGROUND_H */

