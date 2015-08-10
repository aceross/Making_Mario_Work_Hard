#include "CDebugLogging.h"
#include "Define.h"

CDebugLogging CDebugLogging::DebugLogging;

CDebugLogging::CDebugLogging()
{
    fpDebug = NULL;
    DebugLevel = 1;
    LoggingEnabled = true;    
}

void CDebugLogging::Tidy()
{
    if (fpDebug)
        fclose(fpDebug);
    
    fpDebug = NULL;
}

void CDebugLogging::Log(std::string message, int Level)
{
    if ( (Level <= DebugLevel) && LoggingEnabled)
    {
        // Open Log file if not already open
        if (!fpDebug)
        {
            fpDebug = fopen(LOGFILENAME,"w");
            
            if (fpDebug == NULL)
                return;
        }
        
        // Write message to file
        fprintf(fpDebug, "X: %s\n", message.c_str());
        printf("X: %s\n", message.c_str());
    }
}