#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(sound);
}

void SoundEffect::LoadClip(string loadPath)
{
	sound = Mix_LoadWAV(loadPath.c_str());
}

void SoundEffect::Play()
{
	Mix_PlayChannel(-1, sound, 0);
}

void SoundEffect::Stop()
{
	
}