/* 
 * File:   CDebugLogging.h
 * Author: alan
 *
 * Created on January 18, 2013, 1:22 PM
 */

#ifndef CDEBUGLOGGING_H
#define	CDEBUGLOGGING_H

#include <string>
#include <stdio.h>

class CDebugLogging
{
    public:

        static CDebugLogging DebugLogging;

        CDebugLogging();

        void    Log(std::string message, int Level);
        void    Tidy();

        bool    LoggingEnabled;
        int     DebugLevel;
        
    private:
        FILE*   fpDebug;    
};


#endif	/* CDEBUGLOGGING_H */

