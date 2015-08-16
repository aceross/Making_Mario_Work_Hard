#include "../include/CState.h"

CState::CState()
{

}

void CState::WriteText(SDL_Surface* Surf_Dest, const char* text, TTF_Font* font, SDL_Color color)
{
    int X, Y;

    SDL_Surface* fontsurface = TTF_RenderText_Blended(font, text, color);

    X = (WINDOW_WIDTH / 2) - (fontsurface->w / 2);
    Y = (WINDOW_HEIGHT / 2) - (fontsurface->h / 2);

    CSurface::Draw(Surf_Dest, fontsurface, X, Y);
    SDL_FreeSurface(fontsurface);
}
