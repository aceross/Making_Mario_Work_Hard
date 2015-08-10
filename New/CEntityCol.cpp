#include "CEntity.h"
 
std::vector<CEntityCollision> CEntityCollision::EntityCollisionList;
 
CEntityCollision::CEntityCollision() 
{
    this->EntityA = NULL;
    this->EntityB = NULL;
    Complete = false;
}

bool CEntityCollision::RemoveCollision(CEntity* A, CEntity* B)
{
    std::vector<CEntityCollision>::iterator it = EntityCollisionList.begin(); 
    
    for ( ; it != EntityCollisionList.end(); ++it)
    {
        //Check A B
        if ((it->EntityA == A) && (it->EntityB == B))
            it->Complete = true;
      
        // Check B A
        if ((it->EntityA == B) && (it->EntityB == A))
            it->Complete = true;
    }
    
    return true;
}