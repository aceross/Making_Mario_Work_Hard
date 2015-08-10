#ifndef _CMARIO_H_
    #define _CMARIO_H_

#include "CEntity.h"
#include "CFireball.h"

// For Normal Mario
#define MARIO_ANIMATION_COL_NORM        0
#define MARIO_ANIMATION_COL_JUMP        2
#define MARIO_ANIMATION_COL_CLIMB       4
#define MARIO_ANIMATION_COL_DUCK        5
#define MARIO_ANIMATION_COL_SPIN        7
#define MARIO_ANIMATION_NUM_FRAMES      2
#define MARIO_COLLISION_Y_DUCK          32
#define MARIO_COLLISION_WIDTH           15
#define MARIO_COLLISION_X               15
#define MARIO_COLLISION_Y               20

// For Super Mario
#define SUPER_MARIO_ANIMATION_COL_NORM        8
#define SUPER_MARIO_ANIMATION_COL_JUMP        10
#define SUPER_MARIO_ANIMATION_COL_CLIMB       12
#define SUPER_MARIO_ANIMATION_COL_DUCK        13
#define SUPER_MARIO_ANIMATION_COL_SPIN        15
#define SUPER_MARIO_ANIMATION_NUM_FRAMES      3
#define SUPER_MARIO_COLLISION_Y_DUCK          30
#define SUPER_MARIO_COLLISION_WIDTH           13
#define SUPER_MARIO_COLLISION_X               12
#define SUPER_MARIO_COLLISION_Y               3

// For Fire Mario
#define FIRE_MARIO_ANIMATION_COL_NORM        16
#define FIRE_MARIO_ANIMATION_COL_JUMP        18
#define FIRE_MARIO_ANIMATION_COL_CLIMB       20
#define FIRE_MARIO_ANIMATION_COL_DUCK        21
#define FIRE_MARIO_ANIMATION_COL_SPIN        23
#define FIRE_MARIO_ANIMATION_NUM_FRAMES      3
#define FIRE_MARIO_COLLISION_Y_DUCK          30
#define FIRE_MARIO_COLLISION_WIDTH           13
#define FIRE_MARIO_COLLISION_X               12
#define FIRE_MARIO_COLLISION_Y               3

// For all states
#define MARIO_FLAGS             1
#define MARIO_WIDTH             60
#define MARIO_HEIGHT            60
#define MARIO_COLLISION_HEIGHT  0
#define MARIO_MAXSPEED_X        10
#define MARIO_MAXSPEED_Y        13.5
#define MARIO_ZINDEX            10
#define MARIO_GFX               "./gfx/mario.png"
#define MARIO_ANIMATION_NUM_FRAMES_DUCK         1
#define MARIO_ANIMATION_NUM_FRAMES_CLIMB        1
#define MARIO_ANIMATION_NUM_FRAMES_JUMP         1
#define MARIO_ANIMATION_NUM_FRAMES_SPIN         4
#define MARIO_FRAMERATE         100
#define MARIO_FRAMERATE_SPIN    50

enum
{
    NORMAL_MARIO = 0,
    SUPER_MARIO,
    FIRE_MARIO
};

class CMario : public CEntity 
{
    public:
        CMario();
        CMario(CEntity* temp, int params[]);
        
        bool    Load(char* File, int Width, int Height, int NumberOfFrames);
        void    Loop();
        void    Render(SDL_Surface* SDisplay);
        void    Tidy();
        void    Animate();
        bool    OnCollision(CEntity* Entity);
        void    Kill();       
        void    Duck(bool Duck);
        void    Spin(bool Spin);
        void    ChangeMarioState(int state);
        void    ThrowFireball();
        void    DropReservePowerup();
        void    SwitchPowerUp();
        
        int     MarioState;
        int     Animation_NumFrames, Animation_Col_Norm, Animation_Col_Jump, Animation_Col_Climb, Animation_Col_Duck, CollisionY_Duck;
        int     Animation_Col_Spin;
        bool    Spinning;
        unsigned int    FlashingTime;
        unsigned int    SpinTime;
        bool    Hidden;
        
        int     CurrentPowerUp;
        int     ReservePowerUp;
};

#endif


