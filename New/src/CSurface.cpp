
#include "CSurface.h"

CSurface::CSurface() 
{
    
}

SDL_Surface* CSurface::Load(std::string File) 
{    
    SDL_Surface* STemp = NULL;
    SDL_Surface* SReturn = NULL;
    
    if((STemp = IMG_Load(File.c_str())) == NULL)
        return NULL;
    
    SReturn = SDL_DisplayFormatAlpha(STemp);
    
    SDL_FreeSurface(STemp);
    STemp = NULL;
    
    return SReturn;
}

bool CSurface::Draw(SDL_Surface* SDest, SDL_Surface* SSrc, int X, int Y) 
{
    if(SDest == NULL || SSrc == NULL)
        return false;
    
    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(SSrc, NULL, SDest, &DestR);

    return true;
}


bool CSurface::Draw(SDL_Surface* SDest, SDL_Surface* SSrc, int X, int Y, int X2, int Y2, int W, int H) 
{
    if(SDest == NULL || SSrc == NULL) 
        return false;
    
    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_Rect SrcR;

    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;

    SDL_BlitSurface(SSrc, &SrcR, SDest, &DestR);

    return true;
}

bool CSurface::Transparent(SDL_Surface* SDest, int R, int G, int B) 
{
    if(SDest == NULL) 
        return false;
   
    SDL_SetColorKey(SDest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(SDest->format, R, G, B));

    return true;
}


