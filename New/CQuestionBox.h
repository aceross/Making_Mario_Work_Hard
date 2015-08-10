/* 
 * File:   CQuestionBox.h
 * Author: alan
 *
 * Created on December 7, 2012, 2:18 PM
 */

#ifndef CQUESTIONBOX_H
#define	CQUESTIONBOX_H

#include "CBlock.h"
#include "GlobalFunctions.h"


class CQuestionBox : public CBlock
{
    public:
        CQuestionBox();

        CQuestionBox(CEntity* temp, int params[]);
        
        void LoadSettings();
};



#endif	/* CQUESTIONBOX_H */

