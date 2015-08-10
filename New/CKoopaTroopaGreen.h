#ifndef _CKOOPATROOPAGREEN_H_
    #define _CKOOPATROOPAGREEN_H_

#include "CEnemy.h"

class CKoopaTroopaGreen : public CEnemy 
{
    public:
        CKoopaTroopaGreen();

        CKoopaTroopaGreen(CEntity* temp, int params[]);
        
        void LoadSettings();
        
        void GoSecondState(bool scorePoints);
        void GoFirstState();
};

#endif


