#ifndef _CGAME_H_
    #define _CGAME_H_

#include "CState.h"
#include <string>

#include "Define.h"
#include "GlobalFunctions.h"
#include "CSoundManager.h"

#include "CLevel.h"
#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"

#include "CMario.h"
#include "CKoopaTroopaGreen.h"
#include "CQuestionBox.h"
#include "CScreenFurniture.h"
#include "CPipe.h"

class CGame : public CState 
{
    private:
        
        static CGame    Instance;
        CGame();
        SDL_Surface*    SDisplay;
        
        int                             CurrentLevel; // Index for Levels list
        std::vector<std::string>        Levels; // List of levels
        
        void NextLevel();
        
    public:
        void Reset(); 
        
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
        void OnUser(Uint8 type, int code, void* data1, void* data2);             
        
        bool Activate(SDL_Surface* SDisp, int Options[] = NULL);
        void DeActivate();
        void Loop();
        void Render();
        void Tidy();        
        bool InitializeEntities(); 
        
        int     GetCurrentLevelByID();        
        void    LevelComplete();
        void    GameOver();
        void    GameComplete();
        
        static CGame* GetInstance();
};

#endif
