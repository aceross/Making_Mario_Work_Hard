/* 
 * File:   CScreenFurniture.h
 * Author: alan
 *
 * Created on December 8, 2012, 3:25 PM
 */

#ifndef CSCREENFURNITURE_H
#define	CSCREENFURNITURE_H

#include <SDL_ttf.h>
#include "CSurface.h"
#include "GlobalFunctions.h"
#include "Define_HUD.h"

class CScreenFurniture
{
    public:
        CScreenFurniture();
        ~CScreenFurniture();
        
        static CScreenFurniture Furniture;
        
        bool Initialize();
        void Render(SDL_Surface* surface);
        
    protected:

        SDL_Surface*    SHUD;
        SDL_Surface*    SPowerups;
        
        void WriteText(SDL_Surface* Surf_Dest, const char* text, TTF_Font* font, SDL_Color color, int X, int Y);
};


#endif	/* CSCREENFURNITURE_H */

