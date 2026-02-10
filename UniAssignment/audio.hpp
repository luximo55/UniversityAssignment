#pragma once
#include <raylib.h>

class Audio
{
	public:
		Audio();
		~Audio();
		void PlayAudio();
		void PlaySFX(Sound sound);
		Sound music;
		Sound win;
		Sound lose;
		Sound transIn;
		Sound transOut;
};