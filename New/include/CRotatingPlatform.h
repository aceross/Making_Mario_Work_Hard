/* 
 * File:   CRotatingPlatform.h
 * Author: alan
 *
 * Created on February 18, 2013, 3:08 PM
 */

#ifndef CROTATINGPLATFORM_H
#define	CROTATINGPLATFORM_H

#include "CPlatform.h"

#define RP_FLAGS                8
#define RP_ROTATIONSPEED        5
#define RP_NUM_OF_SPOKES        5
#define RP_SPOKE_SIZE           32
#define RP_SPOKE_GFX            "./gfx/spoke.png"
#define RP_BLOCK_GFX            "./gfx/block.png"
#define RP_DEGREE_FRACTIONS     4

struct Spoke
{
    float X;
    float Y;
};

class CRotatingPlatform : public CPlatform
{
    public:
        CRotatingPlatform();
        CRotatingPlatform(CEntity* temp, int params[]) : CPlatform(temp, params)
        {            
            Initialize(params);
        }
        
        void Initialize(int params[]);
        void Loop();
        void Render(SDL_Surface* SDisplay, int X2Offset);
        bool OnCollision(CEntity* Entity);
        
        int OriginX;
        int OriginY;
        
    private:
        int Radius;
        int RotationSpeed;
        int CurrentAngle;
        
        int StartAngle;
        int EndAngle;
        
        int MoveTime;
        
        bool    Oscillate;
        int     Direction; // 1=Clockwise -1=Anti-clockwise
        
        bool    Stopped;
        
        Spoke           Spokes[RP_NUM_OF_SPOKES];
        
        SDL_Surface*    SSpoke;
        SDL_Surface*    SBlock;
        
        float X_at_Radius(int radius, int angle);
        float Y_at_Radius(int radius, int angle);
        
        void FindNewPosition();
};

#endif	/* CROTATINGPLATFORM_H */

