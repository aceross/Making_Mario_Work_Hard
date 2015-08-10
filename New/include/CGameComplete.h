/* 
 * File:   CGameComplete.h
 * Author: alan
 *
 * Created on February 26, 2013, 10:44 AM
 */

#ifndef CGAMECOMPLETE_H
#define	CGAMECOMPLETE_H

#include "CState.h"
#include "CSurface.h"
#include <SDL_ttf.h>
#include "GlobalFunctions.h"

class CGameComplete : public CState
{
    public:
        bool Activate(SDL_Surface* SDisplay, int Options[] = NULL);
        void DeActivate();
        
        void Loop();
        void Render();
        
        static CGameComplete* GetInstance();
        
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        
    private:
        CGameComplete();

        static  CGameComplete     Instance;

        std::ostringstream     Message;
        
        SDL_Surface*    SMessage;
        SDL_Surface*    SDisplay;
        
};

#endif	/* CGAMECOMPLETE_H */

