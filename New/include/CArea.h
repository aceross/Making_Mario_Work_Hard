#ifndef _CAREA_H_
    #define _CAREA_H_

#include "CMap.h"
#include "CBackground.h"
#include <string>
#include <sstream>

class CArea 
{
    public:
        
        std::vector<CMap>       MapList;  // List of all maps in the area
        
        std::string             Filename;
        std::string             MusicFilename;
        
    private:
        int                     AreaWidth;
        int                     AreaHeight;
        
        SDL_Surface*		STileset; // Load the tiles here
        CBackground             Background;
        
    public:
        CArea();

        bool    Load(std::string Level, std::string Area);
        void    Render(SDL_Surface* SDisplay, int CameraX, int CameraY);
        void    Tidy();
        void    Loop();
        
        CMap*	GetMap(int X, int Y); // Returns map at X,Y
        CTile*	GetTile(int X, int Y); // Returns Tile at X,Y
        
        int     GetAreaWidth();
        int     GetAreaHeight(); 
        
        int     GetBackgroundColour();
};

#endif

