#pragma once
#include <raylib.h>

class Player
{
	public:
		Player();
		~Player();
		void Draw();
		void Update(bool isColliding);
		Rectangle GetRect();
		void DrawHitBox(bool isColliding);
	private:
		Texture2D activeSprite;
		Vector2 position;
		int speed;
};