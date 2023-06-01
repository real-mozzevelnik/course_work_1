#ifndef Sounds_h
#define Sounds_h

#include "../Configs.h"
#include <vector>
#include <map>

class Sound
{
    public:
        Sound(const char* filepath);
        ~Sound();
        void Play();
        void Stop();

    private:
        SDL_AudioDeviceID device;
        SDL_AudioSpec audioSpec;
        Uint8 *waveStart;
        Uint32 waveLength;
    
};

class SoundsManager
{
    public:
        static map<int, Sound*> sounds;
        static vector<Sound*> music;
    public:
        static void LoadAudios();
        static void FreeAudios();

};

#endif