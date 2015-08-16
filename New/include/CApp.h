/* 
 * File:   CApp.h
 * Author: alan
 *
 * Created on December 24, 2012, 3:09 PM
 */

#ifndef CAPP_H
#define	CAPP_H

#include <SDL.h>
#include "CStateManager.h"
#include "CFramerate.h"
#include "CEvent.h"
#include "CSurface.h"
#include "GlobalFunctions.h"

class CApp : public CEvent
{
    private:
        bool            Running;

        SDL_Surface*    SDisplay;
        
    public:
        CApp();
        int Execute();
        void OnExit();
        void Tidy();
        void OnEvent(SDL_Event* Event);
        bool Initialize();
        void Loop();
        void Render();
};




#endif	/* CAPP_H */

