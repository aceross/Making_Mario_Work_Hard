/* 
 * File:   CGameOver.h
 * Author: alan
 *
 * Created on February 10, 2013, 7:32 PM
 */

#ifndef CGAMEOVER_H
#define	CGAMEOVER_H

#include "CState.h"
#include "CSurface.h"
#include <SDL_ttf.h>
#include "GlobalFunctions.h"

class CGameOver : public CState
{
    public:
        bool Activate(SDL_Surface* SDisplay, int Options[] = NULL);
        void DeActivate();
        
        void Loop();
        void Render();
        
        static CGameOver* GetInstance();
        
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        
    private:
        CGameOver();

        static  CGameOver     Instance;

        std::ostringstream     Message;
        
        SDL_Surface*    SMessage;
        SDL_Surface*    SDisplay;
        
};

#endif	/* CGAMEOVER_H */

