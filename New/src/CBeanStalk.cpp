
#include "../include/CBeanStalk.h"
#include "../include/CMario.h"
#include "../include/CSoundManager.h"

CBeanStalk::CBeanStalk()
{
    Flags = BEANSTALK_FLAGS;
    Width = BEANSTALK_WIDTH;
    Height = BEANSTALK_HEIGHT;
    NumberOfFrames = BEANSTALK_ANIMATION_NUM_FRAMES;
    Collision_Width = BEANSTALK_COLLISION_WIDTH;
    Collision_Height = BEANSTALK_COLLISION_HEIGHT;
    Collision_X = BEANSTALK_COLLISION_X;
    Collision_Y = BEANSTALK_COLLISION_Y;
    MaxSpeedX = BEANSTALK_MAXSPEED_X;
    MaxSpeedY = BEANSTALK_MAXSPEED_Y;
}

CBeanStalk::CBeanStalk(CEntity* temp, int params[])
{
    // parameter 0: Max Height
    // parmeter  1: Current Height

    if (params[0] != UNINITIALIZED_PARAM)
        MaxHeight = params[0];
    else
        MaxHeight = BEANSTALK_HEIGHT;

    if (params[1] > 0)
        temp->Height = params[1];
    else if (params[1] == 0)
        temp->Height = 0;
    else
        temp->Height = MaxHeight;

    // Offset Y by Height
    temp->Y -= temp->Height;

    temp->Flags = BEANSTALK_FLAGS;
    temp->Width = BEANSTALK_WIDTH;
    temp->NumberOfFrames = BEANSTALK_ANIMATION_NUM_FRAMES;
    temp->Collision_Width = BEANSTALK_COLLISION_WIDTH;
    temp->Collision_Height = BEANSTALK_COLLISION_HEIGHT;
    temp->Collision_X = BEANSTALK_COLLISION_X;
    temp->Collision_Y = BEANSTALK_COLLISION_Y;
    temp->MaxSpeedX = BEANSTALK_MAXSPEED_X;
    temp->MaxSpeedY = BEANSTALK_MAXSPEED_Y;

    PopulateData(temp);

    // Build Dynamic Graphic
    Load(BEANSTALK_GFX, Width, MaxHeight, NumberOfFrames);

    PreviousTime = 0;
    Growing = false;
}

bool CBeanStalk::Load(std::string File, int Width, int Height, int NumberOfFrames)
{
    SDL_Surface* tiles = NULL;

    if((tiles = CSurface::Load(File)) == NULL)
        return false;

    SDL_Surface* SBeanStalk = SDL_CreateRGBSurface(SDL_HWSURFACE,Width,Height,32,
                                    tiles->format->Rmask, tiles->format->Gmask,
                                    tiles->format->Bmask, tiles->format->Amask);

    // Build full size bean-stalk from parts
    int sections = Height / (BEANSTALK_HEIGHT / 2);

    unsigned int tilesize = (tiles->pitch*tiles->h) / 2 ;

    for (int x = 0; x < sections; x++)
    {
        int Y = (x % 2);

        memcpy(SBeanStalk->pixels + (x * tilesize), tiles->pixels + (Y * tilesize), tilesize);
    }

    SEntity = SDL_DisplayFormatAlpha(SBeanStalk);

    this->Width = Width;

    Animation.NumberOfFrames = NumberOfFrames;

    SDL_FreeSurface(tiles);
    SDL_FreeSurface(SBeanStalk);

    ZIndex = 0;
    MinY = Y - Height;

    return true;
}

void CBeanStalk::Loop()
{
    // Grow the Bean Stalk
    if (Growing)
    {
        // Play growing sound ONCE
        static bool SoundPlayed = false;

        if (!SoundPlayed)
        {
            CSoundManager::SoundManager.Play(FX_VINE);
            SoundPlayed = true;
        }

        int GrowthFrameRate = 10;

        if (Height <= MaxHeight)
        {
            // Change Displayed Height of BeanStalk
            if ((PreviousTime + GrowthFrameRate) < SDL_GetTicks())
            {
                if (Y >= MinY)
                    Y -= 1;

                Height += 1;

                PreviousTime = SDL_GetTicks();
            }
        }else
        {
            Growing = false;
            Height = MaxHeight;
        }
    }

    CEntity::Loop();
}

void CBeanStalk::Tidy()
{
    if(SEntity)
        SDL_FreeSurface(SEntity);

    SEntity = NULL;
}

bool CBeanStalk::OnCollision(CEntity* Entity)
{
    SDL_Rect target = Entity->GetTargetBox();

    if ((Entity->Type == ENTITY_TYPE_PLAYER) && (target.x >= X+10 && target.x <= X+10))
    {
        // Player is on the ladder
        ((CMario*)Entity)->OnBeanStalk = this;
        Entity->Flags = 0; // Disable gravity whilst on ladder
    }

    return true;
}
