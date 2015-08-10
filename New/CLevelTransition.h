/* 
 * File:   CLevelTransition.h
 * Author: alan
 *
 * Created on February 10, 2013, 10:49 AM
 */

#ifndef CLEVELTRANSITION_H
#define	CLEVELTRANSITION_H

#include "CState.h"


class CLevelTransition : public CState
{
    public:
        bool Activate(SDL_Surface* SDisplay, int Options[] = {0});
        void DeActivate();
        
        void Loop();
        void Render();
        
        static CLevelTransition* GetInstance();
        
        int     CurrentLevel;
    private:
        CLevelTransition();

        static  CLevelTransition     Instance;
        
        unsigned int    MessageStartTime;
        bool            LevelCompleteShown;
        bool            NewLevelShown;
        bool            GameInitialized;
        std::ostringstream     Message;
        
        SDL_Surface*    SMessage;
        SDL_Surface*    SDisplay;
       
};

#endif	/* CLEVELTRANSITION_H */

