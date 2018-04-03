#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include <string>

using namespace std;

class SoundEffect {
public:
	SoundEffect();
	~SoundEffect();

	void LoadClip(string loadPath);
	void Play();
	virtual void Stop();

protected:
	Mix_Chunk* sound = NULL;
	int channel;
};

#endif