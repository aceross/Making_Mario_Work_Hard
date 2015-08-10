/* 
 * File:   CGoomba.h
 * Author: alan
 *
 * Created on December 23, 2012, 10:26 AM
 */

#ifndef CGOOMBA_H
#define	CGOOMBA_H

#include "CEnemy.h"

class CGoomba : public CEnemy 
{
    public:
        CGoomba();

        CGoomba(CEntity* temp, int params[]);
        
        void LoadSettings();
        void GoSecondState();
        void GoFirstState();
        	
};

#endif	/* CGOOMBA_H */

