
#include "CGate.h"
#include "CGateBar.h"
#include "CLevel.h"

CGate::CGate()
{
    Flags = GATE_FLAGS;
    Width = 0;
    Height = 0;
    NumberOfFrames = GATE_ANIMATION_NUM_FRAMES;
    Collision_Width = GATE_COLLISION_WIDTH;
    Collision_Height = GATE_COLLISION_HEIGHT;
    Collision_X = GATE_COLLISION_X;
    Collision_Y = GATE_COLLISION_Y;
    MaxSpeedX = GATE_MAXSPEED_X;
    MaxSpeedY = GATE_MAXSPEED_Y;
}

CGate::CGate(CEntity* temp, int params[])
{  
    GateType = params[0];
    
    if (GateType == GATE_TYPE_MIDWAY)
    {
        temp->Height = (MIDWAY_HEIGHT / MIDWAY_SECTION_HEIGHT) * MIDWAY_SECTION_HEIGHT;
        temp->Width = MIDWAY_WIDTH;
        SectionHeight = MIDWAY_SECTION_HEIGHT;
        Gate_Gfx = MIDWAY_GATE_GFX;
        
        CLevel::Level.MidwayGate = this;
    }
    else if (GateType = GATE_TYPE_GIANT)
    {
        temp->Height = (GIANT_HEIGHT / GIANT_SECTION_HEIGHT) * GIANT_SECTION_HEIGHT ;
        temp->Width = GIANT_WIDTH;  
        SectionHeight = GIANT_SECTION_HEIGHT;
        Gate_Gfx = GIANT_GATE_GFX;
    }
    
    // Offset Y by Height
    temp->Y -= temp->Height;
    temp->Flags = GATE_FLAGS; 
    temp->NumberOfFrames = GATE_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = GATE_COLLISION_WIDTH;
    temp->Collision_Height = GATE_COLLISION_HEIGHT;
    temp->Collision_X = GATE_COLLISION_X;
    temp->Collision_Y = GATE_COLLISION_Y;
    temp->MaxSpeedX = GATE_MAXSPEED_X;
    temp->MaxSpeedY = GATE_MAXSPEED_Y;
            
    temp->SetSurface(CSurfaceManager::SurfaceManager.GetSurface(Gate_Gfx));
    
    PopulateData(temp);
    
    Load(Gate_Gfx, Width, Height, NumberOfFrames);
}

bool CGate::Load(std::string File, int Width, int Height, int NumberOfFrames) 
{   
    SDL_Surface* tiles = NULL;

    if((tiles = CSurface::Load(File)) == NULL)
        return false;

    // Create surface to draw gate on
    SDL_Surface* SGate = SDL_CreateRGBSurface(SDL_HWSURFACE, Width,Height,32,
                                    tiles->format->Rmask, tiles->format->Gmask,
                                    tiles->format->Bmask, tiles->format->Amask);

    // Build full size gate from parts
    int sections = Height / SectionHeight;

    // Size of Tile in Bytes
    unsigned int tilesize = (tiles->pitch*tiles->h) / 2 ;
    
    // Draw Top of Gate
    memcpy(SGate->pixels, tiles->pixels, tilesize);
    
    // Draw pole
    for (int x = 1; x < sections; x++)    
        memcpy(SGate->pixels + (x * tilesize), tiles->pixels + tilesize, tilesize);

    SEntity = SDL_DisplayFormatAlpha(SGate);
    
    this->Width = Width;
    this->Height = Height;

    Animation.NumberOfFrames = NumberOfFrames;

    SDL_FreeSurface(tiles);
    SDL_FreeSurface(SGate);
    
    tiles = NULL;
    SGate = NULL;
    
    // Load in bar 
    CGateBar bar;
    
    bar.ParentGate = this;
    bar.GateType = GateType;
    
    CEntity::EntityList.push_back(new CGateBar(&bar)); 

    return true;
}

void CGate::Tidy()
{
    if (SEntity)
        SDL_FreeSurface(SEntity);
    
    SEntity = NULL;
}



