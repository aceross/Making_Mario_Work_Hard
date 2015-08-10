#include <SDL/SDL_keysym.h>
#include "CGame.h"
#include "CDebugLogging.h"

void CGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
    CMario* player = GetPlayer();
    
    if (!player)
        return;
    
    switch(sym) 
    {
        case SDLK_LEFT: 
        {	
            if (!player->Ducking)
            {
                player->MoveLeft = true;
                player->FaceLeft = true;
                player->FaceRight = false;                
            }
            break;
        }
        
        case SDLK_RIGHT: 
        {
            if (!player->Ducking)
            {
                player->MoveRight = true;
                player->FaceLeft = false;
                player->FaceRight = true;                   
            }
            break;
        }
        
        case SDLK_UP:
        {
            if (player->OnBeanStalk != NULL)
            {
                player->MoveUp = true;
                player->MoveDown = false;
            }
            break;
        }

        case SDLK_DOWN:
        {
            if (player->OnBeanStalk)
            {
                player->MoveUp = false;
                player->MoveDown = true;
            } else if (player->InPipe)
            {
                ((CPipe*)player->InPipe)->Transport(player);
                
            } else // duck down           
                player->Duck(true);
            
            break;
        }
        
        case SDLK_SPACE: {
            player->Jump();
            break;
        }
        
        case SDLK_a: {
            player->CanCarry = true; // Try to pick something up
            
            if (player->MarioState == FIRE_MARIO)
                player->ThrowFireball();
            
            break;
        }
        
        case SDLK_s: {
            player->Spin(true);
            break;
        }
                
        default: {
        }
    }
}

void CGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
    CMario* player = GetPlayer();
    
    switch(sym) 
    {
        case SDLK_LEFT: {
                player->MoveLeft = false;
                break;
        }
        case SDLK_RIGHT: {
                player->MoveRight = false;
                break;
        }
        
        case SDLK_UP:
        {
            player->MoveUp = false;     
            player->StopMove();
            break;
        }

        case SDLK_DOWN:
        {            
            player->MoveDown = false; 
            player->Duck(false);            
            break;
        }
        
        
        case SDLK_g: {
            CLevel::Level.showGrid = (CLevel::Level.showGrid == true) ? false : true;
            break;
        }
        case SDLK_r: {
            Reset();
            break;
        }
        
        case SDLK_d: // Enable / Disable Debug Logging
        {
            CDebugLogging::DebugLogging.LoggingEnabled = (CDebugLogging::DebugLogging.LoggingEnabled) ? false : true;
            break;
        }
        
        case SDLK_a: {
            
            player->CanCarry = false;
            
            if (player->Carrying)
            {
                // Drop or throw the carried object                                     
                if (player->MoveLeft || player->MoveRight) // throw                                        
                    player->Throw();                    
                else // drop
                    player->Drop();                
               
            }
            player->Carrying = NULL;
            break;
        } 
        
        case SDLK_s: {
            player->Spin(false);
            break;
        }
        
        case SDLK_RETURN: {
            player->SwitchPowerUp();
            break;
        }
        
        case SDLK_q: {
            CLevel::Level.SetCurrentArea(CLevel::Level.GetCurrentAreaID() + 1);
        }
        
        default: {
        }
    }
}

void CGame::OnUser(Uint8 type, int code, void* data1, void* data2) 
{
    // USER EVENTS
   
    switch (code)
    {
        case GAME_EVENT_RESET:
            Reset();
            break;
            
        case GAME_EVENT_LEVEL_COMPLETE:
            LevelComplete();
            break;
            
        case GAME_EVENT_GAMEOVER:
            GameOver();
            break;
    }
    
}