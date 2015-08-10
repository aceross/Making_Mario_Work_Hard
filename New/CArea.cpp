#include <SDL/SDL_video.h>
#include "CArea.h"
#include "CDebugLogging.h"
#include "CMario.h"
#include "CSoundManager.h"

CArea::CArea() 
{
    AreaWidth = 0;
    AreaHeight = 0;    
    STileset = NULL;
}

bool CArea::Load(std::string Level, std::string Area)
{    
    Tidy();
    
    std::ostringstream path;
    path << MAPS_FOLDER << Level << "/" << Area;
    
    Filename = path.str();
    
    FILE* f = fopen(path.str().append("/area").c_str(), "r");

    if(f == NULL) return false;
    
    // Read name of Tileset file and load it
    char TilesetFile[255];
    fscanf(f, "%s\n", TilesetFile);

    if((STileset = CSurface::Load(TilesetFile)) == false) 
    {
        fclose(f);
        return false;
    }
    
    // Load background
    // Format: Path_to_Background_Image bgSpeed bgFrames
   
    char BackgroundConfig[256];
    fgets(BackgroundConfig,255,f);
    Background.Load(BackgroundConfig);
    
    // Load Music Filename
    char music_file[256];
    fgets(music_file,255,f);
    
    music_file[strlen(music_file) - 1] = '\0';
    
    std::string MusicPath = MUSIC_PATH;
    MusicPath.append(music_file);
    
    MusicFilename = MusicPath;
    
    // Get area size
    fscanf(f, "%d\n", &AreaWidth);
    fscanf(f, "%d\n", &AreaHeight);
    
    // Load map files from area file
    for(int X = 0; X < AreaWidth; X++) 
    {
        for(int Y = 0; Y < AreaHeight; Y++) 
        {
            char MapFile[255];

            fscanf(f, "%s ", MapFile);

            CMap tempMap;
            
            if(tempMap.Load(Level, Area, MapFile) == false) 
            {
                fclose(f);
                return false;
            }

            tempMap.Surf_Tileset = STileset; // Pass through the tile set to the map
            
            tempMap.AreaX = X;
            tempMap.AreaY = Y;
            
            MapList.push_back(tempMap); // Add map to map list
        }
        fscanf(f, "\n");
    }

    fclose(f);

    // Logging
    std::ostringstream msg;
    msg << "Level: " << Level << " Area: " << Area << " Loaded Successfully";
    CDebugLogging::DebugLogging.Log(msg.str(), 1);
    
    return true;
}

void CArea::Loop()
{
    // Play Music
    if (!Mix_PlayingMusic())
    {
        CSoundManager::SoundManager.LoadMusic(MusicFilename);
        CSoundManager::SoundManager.PlayMusic(); 
    }
    
    // Background loop includes commands for animated backgrounds
    Background.Loop();
}

void CArea::Render(SDL_Surface* SDisplay, int CameraX, int CameraY) 
{
    // Draw Background First
    Background.Render(SDisplay, CameraX, CameraY);

    // Get map size in Pixels
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    // Find the 4 maps that surround the current location and render just those
    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaWidth);
    
    for(int i = 0; i < 4; i++) 
    {
        unsigned int ID = FirstID + ((i / 2) * AreaWidth) + (i % 2);

        if (ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % AreaWidth) * MapWidth) + CameraX;
        int Y = ((ID / AreaWidth) * MapHeight) + CameraY;

        MapList[ID].Render(SDisplay, X, Y); 
    }
    
}

void CArea::Tidy() 
{
    if(STileset)
        SDL_FreeSurface(STileset);

    STileset = NULL;
    
    Background.Tidy();
    
    // For Each map Tidy
    for (int x=0, len=MapList.size(); x < len; x++)
        MapList[x].Tidy();
    
    MapList.clear();
}

CMap* CArea::GetMap(int X, int Y) 
{
    // Get map size in Pixels
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    unsigned int ID = X / MapWidth;
    ID = ID + ((Y / MapHeight) * AreaWidth);

    if(ID < 0 || ID >= MapList.size())
        return NULL;
    
    return &MapList[ID];
}

CTile* CArea::GetTile(int X, int Y) 
{
    // Get map size in Pixels
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    CMap* Map = GetMap(X, Y);

    if(Map == NULL) return NULL;

    X = X % MapWidth;
    Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}

int  CArea::GetAreaWidth()
{
   return AreaWidth * (MAP_WIDTH * TILE_SIZE);
}

int  CArea::GetAreaHeight()
{
   return AreaHeight * (MAP_HEIGHT * TILE_SIZE);
}

int CArea::GetBackgroundColour()
{
    return Background.BackgroundColour;
}