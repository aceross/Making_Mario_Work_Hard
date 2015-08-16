#include "CLevel.h"
#include <sstream>
#include "CSoundManager.h"

CLevel CLevel::Level;

CLevel::CLevel() 
{   
    STile_Grid = NULL;    
    SMap_Edge = NULL;
    STile_Highlight = NULL;
    
    MidwaySavePoint = false;
    showGrid = false;
    
    CurrentArea = 0;
}

bool CLevel::Load(std::string File) 
{
    Tidy();
    
    MidwaySavePoint = false;
    
    if((STile_Grid = CSurface::Load("./gfx/grid.png")) == false) return false;
    if((SMap_Edge = CSurface::Load("./gfx/mapedge.png")) == false) return false;
    if((STile_Highlight = CSurface::Load("./gfx/gridhighlight.png")) == false) return false;
    
    // BuildPath to Level files
    std::ostringstream LevelPath;
    LevelPath << MAPS_FOLDER << File << "/level";

    FILE* f = fopen(LevelPath.str().c_str(), "r");

    if(f == NULL) return false;
   
    // Read in Areas from file
    
    CurrentArea = 0;
    
    char buffer[255];
    
    // Get Level Name
    fgets(buffer, 255, f);
    
    buffer[strlen(buffer) - 1] = '\0';
    
    LevelName = buffer;

    // Reset Dragon Coins for Level
    CAreaScoring::AreaScoring.ResetDragonCoins();
    
    while (fgets(buffer, 255, f))
    {
        // overwrite \n with \0
        buffer[strlen(buffer) - 1] = '\0';
               
        CArea newarea;
        newarea.Load(File, buffer);
        
        // Load Area into vector
        AreaList.push_back(newarea);
    }
    
    fclose(f);
    
    return true;
}

void CLevel::Tidy() 
{
    if(STile_Grid)
        SDL_FreeSurface(STile_Grid);
    
    if (SMap_Edge)
        SDL_FreeSurface(SMap_Edge);

    if (STile_Highlight)
        SDL_FreeSurface(STile_Highlight);
    
    STile_Grid = NULL;    
    SMap_Edge = NULL;
    STile_Highlight = NULL;
    
    MidwayGate = NULL;
    
    // Tidy up each loaded area
    for (int x=0, len=AreaList.size(); x < len; x++)
        AreaList[x].Tidy();
    
    AreaList.clear();
}

void CLevel::SetCurrentArea(int area)
{
    CurrentArea = area % AreaList.size();
    CSoundManager::SoundManager.LoadMusic(GetCurrentArea()->MusicFilename);
    CSoundManager::SoundManager.PlayMusic();     
}

CArea* CLevel::GetCurrentArea()
{
    return &AreaList[CurrentArea];
}

int CLevel::GetCurrentAreaID()
{
    return CurrentArea;
}