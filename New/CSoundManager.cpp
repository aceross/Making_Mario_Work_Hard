#include <string>

#include "CSoundManager.h"
#include "CDebugLogging.h"

CSoundManager   CSoundManager::SoundManager;

CSoundManager::CSoundManager()
{
    Music = NULL;
}

bool CSoundManager::Initialize()
{
    // SDL_Mixer Setup
    
    if (!SOUND_ENABLED)
        return false;
       
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        return false;
    
    CDebugLogging::DebugLogging.Log("Sound System Initialized", 1); 
    
    return true;
}

// Load a specified Sound File
bool CSoundManager::Load(std::string File)
{
    Mix_Chunk* TempSound = NULL;
    
    char msg[255];
    sprintf(msg,"Loading Sound: %s", File.c_str());  
    CDebugLogging::DebugLogging.Log(msg,0);
    
    if((TempSound = Mix_LoadWAV(File.c_str())) == NULL)
        return false;
 
    Sounds[File] = TempSound;
    
    return true;
}

bool CSoundManager::LoadMusic(std::string File)
{
    if (!SOUND_ENABLED)
        return false;
    
    // Unload any existing music
    if (Music)
        Mix_FreeMusic(Music);
    
    Music = Mix_LoadMUS(File.c_str());
    
    if (!Music)
    {
        // Log error
        CDebugLogging::DebugLogging.Log(Mix_GetError(),0);
        
        return false;
    }else
        return true;
}

void CSoundManager::Tidy()
{
    for (SoundsMap::const_iterator it = Sounds.begin(); it != Sounds.end(); ++it)
        Mix_FreeChunk(it->second);
    
    Sounds.clear(); 
        
    if (Music)
        Mix_FreeMusic(Music);   
    
    Music = NULL;
}

void CSoundManager::Play(std::string ID, int Loop) 
{    
    if (!SOUND_ENABLED)
        return;
 
    // Check if sound is loaded already. If not, do so
    if (Sounds[ID] == NULL)
        if (Load(ID) == false) return;
    
    Mix_PlayChannel(-1, Sounds[ID], Loop);
}

void CSoundManager::PlayMusic()
{
    if (!SOUND_ENABLED)
        return;
    
    Mix_VolumeMusic(MUSIC_VOLUME);
    
    if (Mix_PlayMusic(Music, -1) == -1)
        CDebugLogging::DebugLogging.Log(Mix_GetError(),0); 
}

void CSoundManager::StopMusic()
{
    Mix_HaltMusic();
}

void CSoundManager::PauseMusic()
{
    Mix_PauseMusic();
}