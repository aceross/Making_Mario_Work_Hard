/* 
 * File:   CBanzaiBill.h
 * Author: alan
 *
 * Created on January 8, 2013, 2:23 PM
 */

#ifndef CBANZAIBILL_H
#define	CBANZAIBILL_H

#include "CEnemy.h"

class CBanzaiBill : public CEnemy 
{
    public:
        CBanzaiBill();

        CBanzaiBill(CEntity* temp, int params[]);
        
        void LoadSettings();
        
        void Loop();
        void Kill();
        
    private:
        bool Paused;
};

#endif	/* CBANZAIBILL_H */

