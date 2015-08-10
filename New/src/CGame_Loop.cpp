
#include "CGame.h"
#include "CAreaScoring.h"
#include "CEventsManager.h"

void CGame::Loop() 
{    
    // Run any Managed Events
    CEventsManager::EventsManager.Loop();
    
    // Run each item in entity list
    int size = CEntity::EntityList.size();
  
    for (int i = 0; i < size; i++) 
    {        
        if(!CEntity::EntityList[i]) continue;        
        CEntity::EntityList[i]->Loop();              
    }
  
    //Collision Events
    for(std::vector<CEntityCollision>::iterator it = CEntityCollision::EntityCollisionList.begin();it != CEntityCollision::EntityCollisionList.end(); ++it) 
    {
        if (it->Complete == false)
        {
            CEntity* EntityA = it->EntityA;
            CEntity* EntityB = it->EntityB;

            if(EntityA == NULL || EntityB == NULL) continue;

            if(EntityA->OnCollision(EntityB))
                EntityB->OnCollision(EntityA);

            // Remove this and it's pair from the list by marking them as Complete
            it->RemoveCollision(EntityA, EntityB);
        }
    }

    CEntityCollision::EntityCollisionList.clear();

    // Handle scoring & Timing
    CAreaScoring::AreaScoring.Loop();
    
    CLevel::Level.GetCurrentArea()->Loop();
   
    // Give some CPU back
    SDL_Delay(1);
}


