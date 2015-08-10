/* 
 * File:   CAreaScoring.h
 * Author: alan
 *
 * Created on December 9, 2012, 9:52 AM
 */

#ifndef CAREASCORING_H
#define	CAREASCORING_H

#define NUMBER_OF_LIVES         5
#define AREA_TIMELIMIT          120000

class CAreaScoring
{
    public:
    
        static CAreaScoring     AreaScoring;
        
        CAreaScoring();
    
        void    Init(bool persistLives = false);
        void    Loop();
        
        void    GetAreaTime(char* areatime);
        int     GetAreaTime();
        
        void    AddCoin(int n);
        void    AddDragonCoin(int n);
        void    ResetDragonCoins();
        void    AddPoints(int p);
        void    AddLife(int life);
        
        int     GetCoins();
        int     GetScore();
        int     GetLives();
        int     GetDragonCoins();
        
    private:

        int             Lives;
        int             Score;
        int             Coins;
        int             DragonCoins;
        
        int             AreaTime; // time to complete level in milliseconds
        unsigned int    AreaTimeStart;  
        int             AreaTimeLimit;    
};



#endif	/* CAREASCORING_H */

