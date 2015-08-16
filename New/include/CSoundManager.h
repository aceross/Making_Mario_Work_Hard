/* 
 * File:   CSoundManager.h
 * Author: alan
 *
 * Created on February 12, 2013, 1:52 PM
 */

#ifndef CSOUNDMANAGER_H
#define	CSOUNDMANAGER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <tr1/unordered_map>
#include "Define_Sounds.h"

typedef std::tr1::unordered_map  <std::string, Mix_Chunk*> SoundsMap;

class CSoundManager
{
    public:
        CSoundManager();
        
        static CSoundManager    SoundManager;
        
        bool    Initialize();
        
        bool    Load(std::string File);    
        void    Tidy();
        void    Play(std::string ID, int Loop = 0);
        
        bool    LoadMusic(std::string File);
        void    PlayMusic();
        
        void    PauseMusic();
        void    StopMusic();
        
    private:
        Mix_Music*      Music;
        SoundsMap       Sounds;
    
};

#endif	/* CSOUNDMANAGER_H */

