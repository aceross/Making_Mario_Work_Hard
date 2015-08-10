/* 
 * File:   CEventsManager.h
 * Author: alan
 *
 * Created on February 10, 2013, 2:36 PM
 */

#ifndef CEVENTSMANAGER_H
#define	CEVENTSMANAGER_H

#include <vector>
#include "SDL.h"

struct ManagedEvent
{
    SDL_Event           Event;
    unsigned int        TriggerTime;
};

class CEventsManager
{
    public:
        CEventsManager();
        
        static CEventsManager   EventsManager;
       
        void Loop();
        void AddEvent(int EventID, int Delay = 0, bool Unique = false); // Unique allows only 1 event of type in queue
        void ClearEvents();
        
    private:
        std::vector<ManagedEvent>       Events;
        
};

#endif	/* CEVENTSMANAGER_H */

