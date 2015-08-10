/* 
 * File:   GlobalFunctions.h
 * Author: alan
 *
 * Created on December 18, 2012, 2:06 PM
 */

#ifndef GLOBALFUNCTIONS_H
#define	GLOBALFUNCTIONS_H

#include "CEntity.h"
#include "CMario.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

extern TTF_Font*       FontSmall;
extern TTF_Font*       FontBig;
extern TTF_Font*       FontHuge;
extern SDL_Color       Red, White, Yellow;
    
bool            InitializeFonts();
void            TidyFonts();

bool            SortByZIndex(CEntity* a, CEntity* b);
bool            SortByType(CEntity* a, CEntity* b);
bool            SortByID(CEntity* a, CEntity* b);

void            CreateCoin(int X, int Y);
void            ShowPoints(int p, int X, int Y);
CMario*         GetPlayer();
CEntity*        GetEntityByID(int ID);

bool            OnScreen(CEntity* entity);
void            ClearEntities();

#endif	/* GLOBALFUNCTIONS_H */

