#include "Sound.h"


Sound::Sound()
{
	soundEffect = NULL;
	channel = -1;


}


Sound::~Sound()
{
}

void Sound::Play(int loops)
{
	channel = Mix_PlayChannel(-1, soundEffect, loops);
}

void Sound::Stop()
{
	Mix_HaltChannel(channel);
}

//void SoundEffect::playOneShot()
//{
//	Mix_PlayMusic(soundByte, 1);
//}

void Sound::Load(string path)
{
	soundEffect = Mix_LoadWAV(path.c_str());

}
