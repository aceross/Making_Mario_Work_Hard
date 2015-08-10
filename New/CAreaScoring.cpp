#include <SDL/SDL_timer.h>
#include "CAreaScoring.h"
#include "GlobalFunctions.h"
#include "CLevel.h"
#include "CEventsManager.h"


CAreaScoring    CAreaScoring::AreaScoring;

CAreaScoring::CAreaScoring()
{
    Score = 0;
    Coins = 0;
    DragonCoins = 0;
}

void CAreaScoring::Init(bool persistLives)
{
    if (!persistLives)
    {
        Lives = NUMBER_OF_LIVES;
        Coins = 0;
        Score = 0;                
    }
    
    DragonCoins = 0;
    AreaTimeLimit = AREA_TIMELIMIT;
    AreaTimeStart = SDL_GetTicks();
    AreaTime = AreaTimeLimit - (SDL_GetTicks() - AreaTimeStart);
}

void CAreaScoring::Loop()
{    
    if (AreaTime <= 0)
    {
        // Times Up!
        AddLife(-1);
    }else
        AreaTime = AreaTimeLimit - (SDL_GetTicks() - AreaTimeStart);
}

void CAreaScoring::GetAreaTime(char* areatime)
{   
    int minutes = (AreaTime / 1000) / 60;
    int seconds = (AreaTime / 1000) % 60;
    
    sprintf(areatime,"%d:%02d",minutes,seconds);   
}

// Returns AreaTime in Seconds
int CAreaScoring::GetAreaTime()
{   
    return AreaTime / 1000 ; 
}

void CAreaScoring::AddCoin(int n)
{
    Coins += n;
    
    if (Coins >= 100) // Add a life when 100 coins reached
    {
        AddLife(1);
        Coins = 0;
    }
}

/* 
 * Dragon Coin specific rules
 * 
 * at least 5 per level - collect all 5 to get extra life
 * each one above 5 gives extra life
 */
void CAreaScoring::AddDragonCoin(int n)
{
    DragonCoins += n;
    
    if (DragonCoins >= 5)
        AddLife(1);
}

void CAreaScoring::AddPoints(int p)
{
    Score += p;
}

int CAreaScoring::GetCoins()
{
    return Coins;
}

int CAreaScoring::GetScore()
{
    return Score;
}

int CAreaScoring::GetLives()
{
    return Lives;
}

void CAreaScoring::AddLife(int life)
{
    CMario* player = GetPlayer();
    
    if (player)
    {        
        if (player->isDead()) // Player is already dead so do nothing
            return;

        if (life < 0)
        {   
            if (player->FlashingTime) // Player has recently de-supered
                return;

            // Check for Super-ness    
            if (player->MarioState > NORMAL_MARIO)
            {        
                player->FlashingTime = SDL_GetTicks();

                player->ChangeMarioState(NORMAL_MARIO);
                return;            
            }else
            {
                Lives += life;
                player->Kill(); 

                if (Lives <= 0) // GAME OVER!      
                    CEventsManager::EventsManager.AddEvent(GAME_EVENT_GAMEOVER, 2000, true);              
            }            
        } 
        else 
            Lives += life;  
    }
}

void CAreaScoring::ResetDragonCoins()
{
    DragonCoins = 0;
}

int CAreaScoring::GetDragonCoins()
{
    return DragonCoins;
}