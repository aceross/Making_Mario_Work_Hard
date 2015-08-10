#include "CGame.h"
#include "CAreaScoring.h"
#include "CPoints.h"
#include "CPlatform.h"
#include "CBeanStalk.h"
#include "CGoomba.h"
#include "CRex.h"
#include "CPowerUp.h"
#include "CBanzaiBill.h"
#include "CPipe.h"
#include "CDebugLogging.h"
#include "CRotatingBlock.h"
#include "CPiranhaPlant.h"
#include "CDragonCoin.h"
#include "CFireball.h"
#include "CGate.h"
#include "CRotatingPlatform.h"
#include "CStretchBlock.h"
#include "CPButton.h"

#include <string>
#include <algorithm>
#include <bits/stl_vector.h>


bool CGame::Activate(SDL_Surface* SDisp, int Options[]) 
{    
    SDisplay = SDisp;
    
    // Load Game
    
    // Load List of Levels From Config File - game
    std::ostringstream GamePath;
    GamePath << MAPS_FOLDER << "/game";

    FILE* f = fopen(GamePath.str().c_str(), "r");

    if(f == NULL) return false;
   
    // Read in Levels from file    
    char buffer[255];
    
    while (fgets(buffer, 255, f))
    {
        // overwrite \n with \0
        buffer[strlen(buffer) - 1] = '\0';
        
        Levels.push_back(buffer);
    }
    
    fclose(f);    
    
    CLevel::Level.Load(Levels[CurrentLevel]);
    
    if (InitializeEntities() == false)
        return false;
    
    // Start scoring & Timing
    CAreaScoring::AreaScoring.Init();
    
    // Start the HUD graphics System
    if (CScreenFurniture::Furniture.Initialize() == false)
        return false;
        
    // Reset the Framerate to avoid big difference in FPS between States
    CFramerate::FPSControl.Reset();
    
    return true;
}

void CGame::DeActivate()
{
    Tidy();
}

bool CGame::InitializeEntities()
{
    // Empty Entity List
    ClearEntities();
    
    // Clear Entity Surfaces
    CSurfaceManager::SurfaceManager.Tidy();
       
    for (int x = 0; x < CLevel::Level.AreaList.size(); x++)
    {
        std::string playerfile = CLevel::Level.AreaList[x].Filename;   
        playerfile.append("/entities");

        FILE* f = fopen(playerfile.c_str(), "r");

        if(f == NULL) return false;    

        char buffer[255];

        while(fgets(buffer,255,f))
        {
            if (buffer[0] == '#' || buffer[0] == '\n') // allow # to comment out lines. Allow for blank lines
                continue;

            CEntity temp;
            
            temp.AreaID = x;
            
            /*         
             * FILE FORMAT
             * 
             * ID, Type, FollowPath, LoopPath, param1, param2, param3, param4 
             * X,Y; X1,Y1; X2,Y2; ....
             *          
             * params vary by entity type
             * Uninitialized value of -999 = UNINITIALIZED_PARAM
             */

            int params[5] = {UNINITIALIZED_PARAM};

            int tempFollowPath, tempLoopPath;

            sscanf(buffer,  "%d, %d, %d, %d, %d, %d, %d, %d, %d\n", 
                            &temp.ID, &temp.Type, &tempFollowPath, &tempLoopPath, &params[0], &params[1], &params[2], &params[3], &params[4]);

            temp.FollowPath = tempFollowPath;
            temp.LoopPath = tempLoopPath;

            // Load Path co-ordinates
            fgets(buffer,255,f);

            char*   coord = strtok(buffer,";");
            int     counter = 0;

            while (coord != NULL)
            {
                // split coord
                location tempLoc;
                int x = sscanf(coord, "%f,%f", &tempLoc.X, &tempLoc.Y);

                if (x > 0)
                {
                    if (counter == 0) // Populate the starting position
                    {
                        temp.X = tempLoc.X;
                        temp.Y = tempLoc.Y;
                    }

                    temp.Path.push_back(tempLoc);
                    temp.PathIndex = 1; // It starts at 0 so set it to goto the Next way-point

                    counter++;
                }

                coord = strtok(NULL,";");
            }

            temp.SDisplay = SDisplay;

            // Increase Entity Counter
            if (temp.ID > CEntity::EntityCounter)
                CEntity::EntityCounter = temp.ID;
            else
                CEntity::EntityCounter++;
            
            switch (temp.Type)
            {
                case ENTITY_TYPE_PLAYER:                    
                    CEntity::EntityList.push_back(new CMario(&temp, params));
                    break;

                case ENTITY_TYPE_KOOPA_TROOPA_GREEN:
                    CEntity::EntityList.push_back(new CKoopaTroopaGreen(&temp, params));
                    break;

                case ENTITY_TYPE_QUESTIONBOX:
                    CEntity::EntityList.push_back(new CQuestionBox(&temp, params));
                    break;

                case ENTITY_TYPE_PLATFORM:
                    CEntity::EntityList.push_back(new CPlatform(&temp, params));
                    break;

                case ENTITY_TYPE_BEANSTALK:
                    CEntity::EntityList.push_back(new CBeanStalk(&temp, params));
                    break;

                case ENTITY_TYPE_GOOMBA:
                    CEntity::EntityList.push_back(new CGoomba(&temp, params));
                    break;

                case ENTITY_TYPE_REX:
                    CEntity::EntityList.push_back(new CRex(&temp, params));
                    break;

                case ENTITY_TYPE_POWERUP:
                    CEntity::EntityList.push_back(new CPowerUp(&temp, params));
                    break;

                case ENTITY_TYPE_BANZAIBILL:
                    CEntity::EntityList.push_back(new CBanzaiBill(&temp, params));
                    break;

                case ENTITY_TYPE_PIPE:
                    CEntity::EntityList.push_back(new CPipe(&temp, params));
                    break;

                case ENTITY_TYPE_ROTATINGBLOCK:
                    CEntity::EntityList.push_back(new CRotatingBlock(&temp, params));
                    break;

                case ENTITY_TYPE_COIN:
                    CEntity::EntityList.push_back(new CCoin(&temp, params));
                    break;
                    
                case ENTITY_TYPE_PIRANHAPLANT:
                    CEntity::EntityList.push_back(new CPiranhaPlant(&temp, params));
                    break;

                case ENTITY_TYPE_DRAGONCOIN:                    
                    CEntity::EntityList.push_back(new CDragonCoin(&temp, params));                    
                    break;

                case ENTITY_TYPE_GATE:
                    CEntity::EntityList.push_back(new CGate(&temp, params));
                    break;

                case ENTITY_TYPE_ROTATINGPLATFORM:
                    CEntity::EntityList.push_back(new CRotatingPlatform(&temp, params));
                    break;

                case ENTITY_TYPE_STRETCHBLOCK:
                    CEntity::EntityList.push_back(new CStretchBlock(&temp, params));
                    break;

                case ENTITY_TYPE_PBUTTON:
                    CEntity::EntityList.push_back(new CPButton(&temp, params));
                    break;
                    
                case ENTITY_TYPE_GENERIC:
                    break;
            }                                
        }

        fclose(f);
    
    }
    
    // Sort the Entities by ZIndex
    std::sort(CEntity::EntityList.begin(), CEntity::EntityList.end(), SortByZIndex);
    
    // CAMERA CONTROL - Force camera to follow Player
    CCamera::Camera.TargetMode = TARGET_MODE_CENTER;
    CCamera::Camera.SetTarget(&GetPlayer()->X, &GetPlayer()->Y);
   
    // Logging
    CDebugLogging::DebugLogging.Log("Entities Initialized Successfully", 1);
    
    return true;    
}

