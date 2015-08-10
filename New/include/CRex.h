/* 
 * File:   CRex.h
 * Author: alan
 *
 * Created on December 23, 2012, 1:04 PM
 */

#ifndef CREX_H
#define	CREX_H

#include "CEnemy.h"

class CRex : public CEnemy 
{
    public:
        CRex();

        CRex(CEntity* temp, int params[]);
        
        void LoadSettings();
        
        void Animate();
};

#endif	/* CREX_H */

