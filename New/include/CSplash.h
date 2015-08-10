/* 
 * File:   CSplash.h
 * Author: alan
 *
 * Created on December 24, 2012, 2:42 PM
 */

#ifndef CSPLASH_H
#define	CSPLASH_H

#include "CState.h"
#include "CSurface.h"

class CSplash : public CState
{
    public:
        bool Activate(SDL_Surface* SDisplay, int Options[] = NULL);
        void DeActivate();
        
        void Loop();
        void Render();
        
        static CSplash* GetInstance(); 
    private:
        CSplash();

        static  CSplash     Instance;
        unsigned int        SplashStartTime;
        
        SDL_Surface*    SSplash;
        SDL_Surface*    SDisplay;
};

#endif	/* CSPLASH_H */

