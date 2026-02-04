#pragma once
#include <raylib.h>
#include "player.hpp"

class TransObject
{
	public:
		TransObject(int choice, int posX, int posY, int goalX, int goalY);
		~TransObject();
		void Draw();
		Texture2D objectSprite;
		Texture2D wreckSprite;
		Texture2D ghostSprite;
		Texture2D cleanSprite;
		bool Collision(Rectangle playerRect, bool isTransformed);
		bool isPickedUp;
		bool pickupable;
		Vector2 position;
		Vector2 goalPos;
		void ReinitializeObjects();
	private:
		void TexturePick(int choice);
		Rectangle GetRect();
		Texture2D sprites[10];
		int spriteScale;
};