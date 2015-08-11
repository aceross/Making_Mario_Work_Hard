#include <string>

#include "../include/CSurfaceManager.h"
#include "../include/CDebugLogging.h"

CSurfaceManager   CSurfaceManager::SurfaceManager;

CSurfaceManager::CSurfaceManager()
{

}

bool CSurfaceManager::Initialize()
{

    return true;
}

// Load a specified Surface
bool CSurfaceManager::Load(std::string File)
{
    SDL_Surface* TempSurface = NULL;

    // Load Surface
    if((TempSurface = CSurface::Load(File)) == NULL)
        return false;

    // Set Transparency color to RGB(255,0,255)
    CSurface::Transparent(TempSurface, 255, 0, 255);

    Surfaces[File] = TempSurface;

    char msg[255];
    sprintf(msg,"Loading Surface: %s", File.c_str());
    CDebugLogging::DebugLogging.Log(msg,0);

    return true;
}

void CSurfaceManager::Tidy()
{
    for (SurfaceMap::const_iterator it = Surfaces.begin(); it != Surfaces.end(); ++it)
        SDL_FreeSurface(it->second);

    Surfaces.clear();
}

SDL_Surface* CSurfaceManager::GetSurface(std::string ID)
{
    // Check is requested surface is already loaded. If not, do so
    if (Surfaces[ID] == NULL)
        if (Load(ID) == false) return NULL;

    return Surfaces[ID];
}
