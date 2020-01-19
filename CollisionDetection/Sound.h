#pragma once
#pragma once

#include "SDL.h"
#include "SDL_mixer.h"

#include <string>
using namespace std;

class Sound
{
public:
	Sound();
	~Sound();

	void Play(int loops);
	void Stop();
	void Load(string path);
	//void playOneShot();


private:
	Mix_Chunk* soundEffect;
	//Mix_Music*	soundByte;
	int channel;

};


