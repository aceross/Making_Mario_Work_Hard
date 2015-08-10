#include "CLevelTransition.h"
#include "CStateManager.h"
#include "CGame.h"

CLevelTransition CLevelTransition::Instance;

CLevelTransition::CLevelTransition()
{
    SMessage = NULL;
    LevelCompleteShown = false;
    NewLevelShown = false;
    GameInitialized = true;
}

bool CLevelTransition::Activate(SDL_Surface* SDisp, int Options[])
{
    if (Options[0] > 0)
        CurrentLevel = Options[0];
    
    Message.str("");
    
    if (CurrentLevel)
    {
        Message << "Level Complete!";        
        GameInitialized = true;
        LevelCompleteShown = false;
    }else
    {
        // It's the 1st Level :: Levels have not yet been loaded so take a peek at 1st level name
        std::ostringstream GamePath;
        GamePath << MAPS_FOLDER << "/game";

        FILE* f = fopen(GamePath.str().c_str(), "r");

        if(f == NULL) return false;

        // Read in Levels from file    
        char buffer[255];
        fgets(buffer, 255, f);
        
        fclose(f);
        
        buffer[strlen(buffer) - 1] = '\0';
        
        std::ostringstream LevelPath;
        LevelPath << MAPS_FOLDER << buffer << "/level";

        printf("%s",LevelPath.str().c_str());
        f = fopen(LevelPath.str().c_str(), "r");

        if(f == NULL) return false;
        
        // Get Level Name
        fgets(buffer, 255, f);
        
        buffer[strlen(buffer) - 1] = '\0';
        
        fclose(f);
        
        Message << buffer;
        LevelCompleteShown = true;
        GameInitialized = false;
    }
    
    SDisplay = SDisp;
    
    MessageStartTime = SDL_GetTicks();
    
    return true;
}

void CLevelTransition::DeActivate()
{
    if (SMessage)
    {
        SDL_FreeSurface(SMessage);
        SMessage = NULL;
    }
    
    CurrentLevel = 0;
}

void CLevelTransition::Loop()
{
    if (LevelCompleteShown == false)
    {
        if (MessageStartTime + 2000 < SDL_GetTicks())
        {
            LevelCompleteShown = true;
            MessageStartTime = SDL_GetTicks();
            Message.str("");
            Message << CLevel::Level.LevelName;           
        }
    }else
    {
        if (MessageStartTime + 3000 < SDL_GetTicks())
        {
            CStateManager::SetAppState(STATE_GAME,SDisplay,false,GameInitialized);
            CSoundManager::SoundManager.StopMusic(); 
        }
    }
}

void CLevelTransition::Render()
{
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WINDOW_WIDTH;
    Rect.h = WINDOW_HEIGHT;
    
    // Clear display
    SDL_FillRect(SDisplay, &Rect, 0);
    
    WriteText(SDisplay, Message.str().c_str(), FontHuge, Yellow);   
 
    SDL_Flip(SDisplay);
}

CLevelTransition* CLevelTransition::GetInstance()
{
    return &Instance;
}

