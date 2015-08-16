
#ifndef _CMAP_H_
    #define _CMAP_H_

#include <SDL.h>
#include <vector>
#include "CTile.h"
#include "CSurface.h"
#include <sstream>

class CMap 
{
    public:
        SDL_Surface*            Surf_Tileset;

    private:
        std::vector<CTile>      TileList;

    public:
        CMap();

        bool Load(std::string Level, std::string Area, std::string Map);

        void Render(SDL_Surface* SDisplay, int MapX, int MapY);
        void Tidy();
        
        CTile*	GetTile(int X, int Y);
        
        std::string Filename;
        int     AreaX, AreaY;
};

#endif
