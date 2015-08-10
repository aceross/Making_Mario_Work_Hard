/* 
 * File:   CLevel.h
 * Author: alan
 *
 * Created on January 26, 2013, 3:08 PM
 */

#ifndef CLEVEL_H
#define	CLEVEL_H

#include "CArea.h"
#include <string>
#include "CDebugLogging.h"
#include "CGate.h"

class CLevel
{
    public:  
        
        CLevel();

        bool    Load(std::string File);        
        void    Tidy();
        CArea*  GetCurrentArea();
        int     GetCurrentAreaID();
        void    SetCurrentArea(int area);
        
        static  CLevel          Level;
        std::vector<CArea>      AreaList;  // List of all areas in the level
        
        std::string             LevelName;
        
        bool                    MidwaySavePoint;
        CGate*                  MidwayGate;
        
        bool                    showGrid; // show or hide the tile grid
        
        SDL_Surface*            STile_Grid;
        SDL_Surface*            SMap_Edge;
        SDL_Surface*            STile_Highlight;
        
    private:
    
        int     CurrentArea;  
};

#endif	/* CLEVEL_H */

