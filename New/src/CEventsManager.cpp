#include "CEventsManager.h"

CEventsManager CEventsManager::EventsManager;

CEventsManager::CEventsManager()
{
    
}

void CEventsManager::Loop()
{
    int CurrentTime = SDL_GetTicks();
    
    for (std::vector<ManagedEvent>::iterator b = Events.begin(); b != Events.end();) 
    { 
        if ((*b).TriggerTime <= CurrentTime)
        {
            // Push Event to queue
            
            SDL_PushEvent(&(*b).Event);
            
            printf("Event Erased: eID: %d Time: %d\n", (*b).Event.user.code, (*b).TriggerTime);
            
            b = Events.erase( b ); // reseat iterator to a valid value post-erase
            
        }
        else
            ++b;            
    } 
}

void CEventsManager::AddEvent(int EventID, int Delay, bool Unique)
{
    if (Unique) // Allow only one of EventID in queue;
    {
        for (int x=0, len=Events.size(); x < len; x++)
            if (Events[x].Event.user.code == EventID)
                return;
    }
    
    SDL_Event event;

    event.type = SDL_USEREVENT;
    event.user.code = EventID;

    ManagedEvent newEvent;

    newEvent.Event = event;
    newEvent.TriggerTime = SDL_GetTicks() + Delay;

    Events.push_back(newEvent);  
    
    printf("Add Event: eID:%d Time:%d\n",EventID,newEvent.TriggerTime);
}

void CEventsManager::ClearEvents()
{
    Events.clear();
}