#pragma once
#include <raylib.h>
#include "player.hpp"

class TransObject
{
	public:
		TransObject(int choice, int posX, int posY);
		~TransObject();
		void Draw(bool isPickedUp);
		Texture2D objectSprite;
		bool Collision(Rectangle playerRect);
		bool isPickedUp;
		Vector2 position;
	private:
		void TexturePick(int choice);
		Rectangle GetRect();
		Texture2D sprites[10];
};