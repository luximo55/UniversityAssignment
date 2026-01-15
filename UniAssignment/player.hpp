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
	private:
		Texture2D activeSprite;
		Texture2D playerSprite;
		Vector2 position;
		int speed;
};