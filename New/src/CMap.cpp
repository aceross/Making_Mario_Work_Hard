#include "CMap.h"
#include "CLevel.h"

CMap::CMap() 
{
    Surf_Tileset = NULL;
    AreaX = 0;
    AreaY = 0;
}


bool CMap::Load(std::string Level, std::string Area, std::string Map)
{
    std::ostringstream path;
    path << MAPS_FOLDER << Level << "/" << Area << "/" << Map;
    
    Filename = path.str();
    
    TileList.clear();
    
    FILE* f = fopen(Filename.c_str(), "r");

    if(f == NULL) return false;
   
    for (int Y = 0; Y < MAP_HEIGHT; Y++) 
    {
        for (int X = 0; X < MAP_WIDTH; X++) 
        {
            CTile tempTile;

            fscanf(f, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            TileList.push_back(tempTile);
        }
        fscanf(f, "\n");
    }

    fclose(f);

    return true;
}

void CMap::Tidy()
{
    
}

void CMap::Render(SDL_Surface* SDisplay, int MapX, int MapY) 
{
    if(Surf_Tileset == NULL) return;
    
    int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;

    int ID = 0;

    for (int Y = 0; Y < MAP_HEIGHT; Y++) 
    {
        for (int X = 0; X < MAP_WIDTH; X++) 
        {
            if(TileList[ID].TypeID == TILE_TYPE_NONE) // Skip if it a NONE tile type. Improves rendering time for empty areas
            {
                    ID++;
                    continue;
            }

            // set position in pixels of this tile on area
            int tileX = MapX + (X * TILE_SIZE);
            int tileY = MapY + (Y * TILE_SIZE);

            // get position in pixels of texture in the tileset image
            int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
            int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

            // Draw tile to surface
            CSurface::Draw(SDisplay, Surf_Tileset, tileX, tileY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
            
            //if (GetTile(tileX, tileY)->Highlight)
             //   CSurface::Draw(SDisplay, CArea::Area.STile_Highlight, tileX, tileY);
            
            if (CLevel::Level.showGrid)
                CSurface::Draw(SDisplay, CLevel::Level.STile_Grid, tileX, tileY);

            ID++;
        }
    }

    if (CLevel::Level.showGrid)
            CSurface::Draw(SDisplay, CLevel::Level.SMap_Edge, MapX, MapY);
}


CTile* CMap::GetTile(int X, int Y) 
{
    unsigned int ID = 0;

    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));

    if(ID < 0 || ID >= TileList.size())
    	return NULL;
    
    return &TileList[ID];
}


