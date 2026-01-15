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
		void SpriteChange(Texture2D objectTexture, bool isColliding);
		bool isTransformed;
		Vector2 position;
	private:
		Texture2D activeSprite;
		Texture2D playerSprite;
		int speed;
};