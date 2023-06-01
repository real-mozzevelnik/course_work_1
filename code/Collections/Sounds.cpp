#include "Sounds.h"

#include "../Game/Game.h"
#include <sstream>


map<int, Sound*> SoundsManager::sounds;
vector<Sound*> SoundsManager::music;

Sound::Sound(const char* filepath)
{
    if (SDL_LoadWAV(filepath, &audioSpec, &waveStart, &waveLength) == nullptr)
        cout << SDL_GetError() << endl;

    device = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (0 == device)
        cout << SDL_GetError() << endl;
}


Sound::~Sound()
{
    SDL_FreeWAV(waveStart);
    SDL_CloseAudioDevice(device);
}


void Sound::Play()
{
    SDL_QueueAudio(device, waveStart, waveLength);
    SDL_PauseAudioDevice(device, 0);
}


void Sound::Stop()
{
    SDL_PauseAudioDevice(device, 1);
}


void SoundsManager::LoadAudios()
{
    Sound* tmp_s = new Sound("../sounds/Coin.wav");
    sounds.insert({COIN_SOUND, tmp_s});
    tmp_s = new Sound("../sounds/enemy_attack.wav");
    sounds.insert({ENEMY_ATTACK_SOUND, tmp_s});
    tmp_s = new Sound("../sounds/death.wav");
    sounds.insert({DEATH_SOUND, tmp_s});
    tmp_s = new Sound("../sounds/jump.wav");
    sounds.insert({JUMP_SOUND, tmp_s});
    tmp_s = new Sound("../sounds/mate.wav");
    sounds.insert({NEXT_LEVEL_SOUND, tmp_s});

    string path;
    stringstream ss;

    for (int i = 0; i < 5; i++)
    {
        ss << "../sounds/level_" << i << ".wav";
        path = ss.str();
        ss.str(string());
        ss.clear();
        tmp_s = new Sound(path.c_str());
        music.push_back(tmp_s);
    }
}


void SoundsManager::FreeAudios()
{
    for (auto i : sounds)
        delete i.second;
    for (auto i : music)
        delete i;
}