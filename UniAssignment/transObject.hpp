#pragma once
#include <raylib.h>
#include "player.hpp"

class TransObject
{
	public:
		TransObject(int choice, int posX, int posY);
		~TransObject();
		void Draw();
		Texture2D objectSprite;
		bool Collision(Rectangle playerRect);
	private:
		void TexturePick(int choice);
		Rectangle GetRect();
		Texture2D sprites[10];
		Vector2 position;
};