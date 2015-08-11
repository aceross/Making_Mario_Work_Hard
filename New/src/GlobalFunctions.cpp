#include "../include/GlobalFunctions.h"
#include "../include/CCoin.h"
#include "../include/CDebugLogging.h"

TTF_Font*       FontSmall;
TTF_Font*       FontBig;
TTF_Font*       FontHuge;
SDL_Color       Red, White, Yellow;

bool SortByZIndex(CEntity* a, CEntity* b)
{
    return a->ZIndex < b->ZIndex;
}

bool SortByType(CEntity* a, CEntity* b)
{
    return a->Type < b->Type;
}

bool SortByID(CEntity* a, CEntity* b)
{
    return a->ID < b->ID;
}

void CreateCoin(int X, int Y)
{
    CCoin coin;

    coin.X = X + 10;
    coin.Y = Y - 40;

    coin.Flags = COIN_FLAGS | ENTITY_FLAG_GRAVITY;

    coin.SetInitialSpeed(-5, -5, 0 , 0);

    location temploc;
    temploc.X = coin.X;
    temploc.Y = coin.Y;
    coin.Path.push_back(temploc);

    CEntity::EntityList.push_back(new CCoin(&coin, NULL));
}

void ShowPoints(int p, int X, int Y)
{
    // show points values on screen
    // Display a coin
    CPoints Points;

    Points.X = X + 10;
    Points.Y = Y - 40;

    location temploc;
    temploc.X = Points.X;
    temploc.Y = Points.Y;
    Points.Path.push_back(temploc);

    char score[10];
    sprintf(score,"%d", p);

    SDL_Surface* surface = TTF_RenderText_Blended(FontSmall, score, White);
    Points.SetSurface(surface);

    Points.Width = surface->w;
    Points.Height = surface->h;

    CEntity::EntityList.push_back(new CPoints(&Points));
}

bool InitializeFonts()
{
    // SDL_TTF Setup
    if (TTF_Init() < 0)
        return false;

    // Load Fonts
    FontHuge = TTF_OpenFont("./fonts/NSMBWii1.ttf",35);
    FontBig = TTF_OpenFont("./fonts/NSMBWii1.ttf",25);
    FontSmall = TTF_OpenFont("./fonts/NSMBWii1.ttf",15);

    // Load colors
    Red.r = 221, Red.g = 58, Red.b = 25;
    White.r = 255, White.g = 255, White.b = 255;
    Yellow.r = 252, Yellow.g = 219, Yellow.b = 116;

    CDebugLogging::DebugLogging.Log("TTF_SDL Initialized", 1);
}

void TidyFonts()
{
    TTF_CloseFont(FontHuge);
    TTF_CloseFont(FontBig);
    TTF_CloseFont(FontSmall);

    FontBig = NULL;
    FontHuge = NULL;
    FontSmall = NULL;
}

CMario* GetPlayer()
{
    // Replace with something better than linear search
    for (int x=0; x< CEntity::EntityList.size(); x++)
        if (CEntity::EntityList[x]->Type == ENTITY_TYPE_PLAYER)
                return (CMario*)(CEntity::EntityList[x]);

    return NULL;
}

CEntity* GetEntityByID(int ID)
{
    // Replace with something better than linear search
    for (int x=0; x< CEntity::EntityList.size(); x++)
        if (CEntity::EntityList[x]->ID == ID)
                return (CEntity*)(CEntity::EntityList[x]);

    return NULL;
}

bool OnScreen(CEntity* entity)
{
    int CamX, CamY;
    bool WithinX = false;
    bool WithinY = false;

    CamX = CCamera::Camera.GetX();
    CamY = CCamera::Camera.GetY();

    if (entity->X > CamX && entity->X < CamX + WINDOW_WIDTH)
        WithinX = true;

    if (entity->Y > CamY && entity->Y < CamY + WINDOW_HEIGHT)
        WithinY = true;

    return (WithinX && WithinY);
}

void ClearEntities()
{
    for (size_t p = 0; p < CEntity::EntityList.size(); ++p)
    {
        CEntity::EntityList[p]->Tidy();
        delete CEntity::EntityList[p];
    }
    CEntity::EntityList.clear();

    CEntity::EntityCounter = 0;
}
