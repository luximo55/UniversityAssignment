#include "audio.hpp"

Audio::Audio()
{
	InitAudioDevice();
	SetMasterVolume(100);
	music = LoadSound("Audio/song.wav");
}

Audio::~Audio()
{
	if (IsSoundPlaying)
		StopSound(music);
	UnloadSound(music);
}

void Audio::PlayAudio()
{
	PlaySound(music);
}