
#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>
#include <string>

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFramerate.h"
#include "CAreaScoring.h"
#include "CSurfaceManager.h"

enum 
{
    ENTITY_TYPE_PLAYER = 0,
    ENTITY_TYPE_GENERIC,                        //1
    ENTITY_TYPE_KOOPA_TROOPA_GREEN,             //2
    ENTITY_TYPE_COIN,                           //3
    ENTITY_TYPE_QUESTIONBOX,                    //4
    ENTITY_TYPE_POINTS,                         //5
    ENTITY_TYPE_PLATFORM,                       //6
    ENTITY_TYPE_BEANSTALK,                      //7
    ENTITY_TYPE_REX,                            //8
    ENTITY_TYPE_GOOMBA,                         //9
    ENTITY_TYPE_POWERUP,                       //10
    ENTITY_TYPE_BANZAIBILL,                     //11
    ENTITY_TYPE_PIPE,                            //12
    ENTITY_TYPE_ROTATINGBLOCK,                   //13
    ENTITY_TYPE_PIRANHAPLANT,                    //14
    ENTITY_TYPE_DRAGONCOIN,                      //15
    ENTITY_TYPE_FIREBALL,                        //16
    ENTITY_TYPE_GATE,                            //17
    ENTITY_BLOCK_PIECE,                          //18
    ENTITY_TYPE_ROTATINGPLATFORM,                //19
    ENTITY_TYPE_STRETCHBLOCK,                    //20
    ENTITY_TYPE_PBUTTON                         //21
};

enum 
{
    ENTITY_FLAG_NONE 	= 0,
    ENTITY_FLAG_GRAVITY	= 0x00000001,
    ENTITY_FLAG_GHOST	= 0x00000002,
    ENTITY_FLAG_MAPONLY	= 0x00000004,
    ENTITY_FLAG_PLAYERONLY = 0x00000008         // Like Ghost but has normal collision with player
};

struct location
{
    float       X;
    float       Y;    
};

class CEntity 
{
    public:
        static std::vector<CEntity*>    EntityList;
        static int      EntityCounter;
        
    protected:
        CAnimation      Animation;

        SDL_Surface*    SEntity;
        
        // Current speed in either direction
        float	SpeedX, SpeedY;

        // Current Acceleration in either direction
        float	AccelX, AccelY;

        bool    CanJump; // Can only jump if touching the floor (i.e. SpeedY = 0)
        
        // Specify which frame of animation to show
        int	CurrentFrameCol, CurrentFrameRow;

        int     LoopInc;
        
        int     CreationTime;

        bool	Dead;
        int     DeathTime;
        int     DeathDelay;
        
        // GENERAL ENTITY CONSTANT SETTINGS
        int CONST_ANIMATION_FRAMERATE;
        int CONST_ANIMATION_NUM_FRAMES;
        int CONST_FLAGS;           
        int CONST_WIDTH;            
        int CONST_HEIGHT;           
        int CONST_COLLISION_WIDTH;   
        int CONST_COLLISION_HEIGHT;  
        int CONST_COLLISION_X;      
        int CONST_COLLISION_Y;     
        float CONST_MAXSPEED_X;      
        float CONST_MAXSPEED_Y;
        std::string CONST_GFX;          
        int CONST_POINTS_EARNED;
        
        bool    RemoveFromList();
               
    public:
        int     ID;        
        int     AreaID;
        
        // Current Position in area
        float	X, Y;       

        float   MinX, MinY, MaxX, MaxY;
        
        bool                    FollowPath;
        bool                    LoopPath;
        int                     PathIndex;
        std::vector<location>   Path;
        
        // Size of entity image
        int	Width, Height;

        int     NumberOfFrames;

        /*
         *  Sets the target box for the purposes of collision detection
         *  The collision box does not need to be the same size or position as the entities sprite
         *  Define the target box using these 4 variables
         * 
         *  Collision_Width & Collision_Height are NOT the width and height of the target box but are
         *  instead the indent from the right and bottom of the original sprite
         */
        int     Collision_X, Collision_Y, Collision_Width, Collision_Height;
        
        // Are we moving Left or Right?
        bool	MoveLeft, MoveRight;
        bool    FaceLeft, FaceRight;
        
        bool    MoveUp, MoveDown;
        
        bool    Ducking;
        
        // Have we reached the edge of the screen?
        bool    AtLeftEdge, AtRightEdge;
        
        int	Type, Flags;

        // Set terminal velocity in each direction
        float	MaxSpeedX, MaxSpeedY;
        
        float   Slope_Offset_X, Slope_Offset_Y;
        int     LifeSpan; // Entity dies after specified time limit;        

        // Allow Entity to carry another entity
        CEntity*        Carrying;
        CEntity*        CarriedBy;   
        int             CarryOffsetX, CarryOffsetY;
        bool            CanBeCarried, CanCarry;
        bool            Thrown; 
        
        CEntity*        OnBeanStalk;
        CEntity*        InPipe;
        
        SDL_Surface*    SDisplay;
        
        int             ZIndex;
        int             Points;
        bool            Killable;        
        
    public:
        CEntity();
        
        virtual ~CEntity();

        virtual bool    Load(std::string File, int Width, int Height, int NumberOfFrames);
        virtual void    Loop();
        virtual void    Render(SDL_Surface* SDisplay, int X2Offset = 0);
        virtual void    Tidy();
        virtual void    Animate();
        virtual bool    OnCollision(CEntity* Entity);
        virtual void    Kill();
        virtual void    Duck(bool duck);
        
        bool    Collides(int objectX, int objectY, int objectW, int objectH);
        
        void    Move(float MoveX, float MoveY);
        void 	StopMove();

        bool    Jump();
       
        bool    Above(int Y);
        bool    Above(CEntity* entity, bool Directly = false);
        bool    Below(int Y);
        bool    Below(CEntity* entity, bool Directly = false);

        bool    OnSlope();        
        
        void    SetInitialSpeed(float sX, float sY, float aX, float aY);
        void    SetSurface(SDL_Surface* surface);
        
        void    Throw();
        void    Drop();
        
        SDL_Rect        GetTargetBox();
        SDL_Rect        GetTargetBox(int X, int Y);
        
        bool    isDead();
        
    protected:
        
        void            PopulateData(CEntity* temp);        
        bool            PositionValid(int NewX, int NewY, bool EntityOnly = false);
        
    private:
        void    PathFollowing();
        
        bool 	PositionValid_Tile(CTile* Tile, int X, int Y);
        bool 	PositionValid_Entity(CEntity* Entity, int NewX, int NewY);   
       
};

class CEntityCollision 
{
    public:
        static std::vector<CEntityCollision>	EntityCollisionList;

        CEntity* EntityA;
        CEntity* EntityB;
        
        bool    Complete;
        
        CEntityCollision();
        
        bool RemoveCollision(CEntity* A, CEntity* B);
};

#endif
