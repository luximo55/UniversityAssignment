#include "audio.hpp"

Audio::Audio()
{
	InitAudioDevice();
	SetMasterVolume(100);
	music = LoadSound("Audio/song.wav");
	win = LoadSound("Audio/win.wav");
	lose = LoadSound("Audio/lose.wav");
	transIn = LoadSound("Audio/transIn.wav");
	transOut = LoadSound("Audio/transOut.wav");
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

void Audio::PlaySFX(Sound sound)
{
	PlaySound(sound);
}