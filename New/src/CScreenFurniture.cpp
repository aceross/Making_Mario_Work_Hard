#include "../include/CScreenFurniture.h"
#include "../include/CSurface.h"
#include "../include/Define.h"
#include "../include/CAreaScoring.h"
#include "../include/CLevel.h"
#include "../include/CPowerUp.h"

CScreenFurniture CScreenFurniture::Furniture;

CScreenFurniture::CScreenFurniture()
{
    SHUD = NULL;
    SPowerups = NULL;
};

CScreenFurniture::~CScreenFurniture()
{
    if (SHUD)
        SDL_FreeSurface(SHUD);

    if (SPowerups)
        SDL_FreeSurface(SPowerups);
}

bool CScreenFurniture::Initialize()
{
    // Load HUD Graphics to surface
    if ( (SHUD = CSurface::Load(HUD_IMAGEFILE)) == false)
        return false;

    // Load Power-up logos to surface
    if ( (SPowerups = CSurface::Load(HUD_POWERUP_IMAGEFILE)) == false)
        return false;

    return true;
}

void CScreenFurniture::Render(SDL_Surface* surface)
{
    // Print Screen Furniture i.e. scores, messages etc...

    if (FontBig)
    {
        char lives[10];
        sprintf(lives,"x %d", CAreaScoring::AreaScoring.GetLives());

        char coins[10];
        sprintf(coins,"     %d", CAreaScoring::AreaScoring.GetCoins());

        char dragoncoins[10];
        sprintf(dragoncoins,"%d", CAreaScoring::AreaScoring.GetDragonCoins());

        char score[10];
        sprintf(score,"%d", CAreaScoring::AreaScoring.GetScore());

        char* time = (char*) malloc(sizeof(char) * 7);

        if (time == NULL)
            return;

        CAreaScoring::AreaScoring.GetAreaTime(time);

        CMario* player = GetPlayer();

        if (CLevel::Level.showGrid)
        {
            if (player)
            {
                SDL_Rect target = player->GetTargetBox();
                char position[255];
                sprintf(position, "x:%d y:%d", (int)target.x, (int)target.y + target.h);

                WriteText(surface, position, FontSmall, White, 5, 5);
            }
        }

        WriteText(surface, "mario", FontBig, Red, 30, 25);

        WriteText(surface, lives, FontBig, White, 45, 50);

        WriteText(surface, "time", FontBig, Yellow, 380, 25);

        WriteText(surface, time, FontBig, Yellow, 383, 50);

        WriteText(surface, coins, FontBig, White, 530, 25);

        WriteText(surface, score, FontBig, White, 530, 50);

        // Draw 1 coin logo for each dragon coin
        for (int x=0, num=CAreaScoring::AreaScoring.GetDragonCoins(); x < num; x++)
            CSurface::Draw(surface, SHUD, 150 + (15 * x), 30, HUD_COINS_X, HUD_COINS_Y, 16, HUD_COINS_H);

        CSurface::Draw(surface, SHUD, 150, 55, HUD_STAR_X, HUD_STAR_Y, HUD_STAR_W, HUD_STAR_H);
        WriteText(surface, dragoncoins, FontBig, White, 190, 50);

        CSurface::Draw(surface, SHUD, 275, 30, HUD_RESERVE_X, HUD_RESERVE_Y, HUD_RESERVE_W, HUD_RESERVE_H);

        CSurface::Draw(surface, SHUD, 500, 35, HUD_COINS_X, HUD_COINS_Y, HUD_COINS_W, HUD_COINS_H);

        if (player)
            if (player->ReservePowerUp) // Display the Reserve Item Logo
                CSurface::Draw(surface, SPowerups, POWERUP_X, POWERUP_Y, player->ReservePowerUp * POWERUPS_WH, 0, POWERUPS_WH, POWERUPS_WH);

        free(time);
    }

}

void CScreenFurniture::WriteText(SDL_Surface* Surf_Dest, const char* text, TTF_Font* font, SDL_Color color, int X, int Y)
{
    SDL_Surface* fontsurface = TTF_RenderText_Blended(font, text, color);
    CSurface::Draw(Surf_Dest, fontsurface, X, Y);
    SDL_FreeSurface(fontsurface);
}
