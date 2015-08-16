/* 
 * File:   CPiranhaPlant.h
 * Author: alan
 *
 * Created on February 5, 2013, 10:06 AM
 */

#ifndef CPIRANHAPLANT_H
#define	CPIRANHAPLANT_H

#include "CEnemy.h"

class CPiranhaPlant : public CEnemy
{
    public:
        CPiranhaPlant();

        CPiranhaPlant(CEntity* temp, int params[]);
        
        void LoadSettings();  
        void Animate();
        void Loop();
        
    private:
        int JumpTime;
            
};


#endif	/* CPIRANHAPLANT_H */

