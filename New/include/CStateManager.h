/* 
 * File:   CStateManager.h
 * Author: alan
 *
 * Created on December 24, 2012, 2:32 PM
 */

#ifndef CSTATEMANAGER_H
#define	CSTATEMANAGER_H

#include "CState.h"

enum
{
    STATE_SPLASH,
    STATE_GAME,
    STATE_CREDITS,
    STATE_LEVEL_TRANSITION,
    STATE_GAME_OVER,
    STATE_GAME_COMPLETE
};

class CStateManager
{
    public:
        static void OnEvent(SDL_Event* Event);
        static void Loop();
        static void Render();
        static void SetAppState(int AppStateID, SDL_Surface* SDisplay, bool MaintainCurrent = false, bool AlreadyActive = false);
        static CState* GetAppState();

    private:    
        static CState*       CurrentState;
        static int           CurrentStateID;
    
};


#endif	/* CSTATEMANAGER_H */

