#pragma once
#include <raylib.h>

class Player
{
	public:
		Player();
		~Player();
		void Draw();
		void Update();
		Rectangle GetRect();
		void DrawHitBox(bool isColliding);
		void SpriteChange(Texture2D ghostTexture, bool isColliding);
		bool isTransformed;
		Vector2 position;
		bool gameover;
		Texture2D activeSprite;
		Texture2D playerSprite;
	private:
		int speed;
		int spriteScale;
};