#include "transObject.hpp"

TransObject::TransObject(int choice, int posX, int posY, int goalX, int goalY)
{
	TexturePick(choice);
	isPickedUp = false;
	pickupable = true;
	position.x = posX;
	position.y = posY;
	goalPos.x = goalX;
	goalPos.y = goalY;
}

TransObject::~TransObject()
{
	UnloadTexture(objectSprite);
}

void TransObject::TexturePick(int choice)
{
	switch (choice)
	{
		case 0:
			objectSprite = LoadTexture("Sprites/table.png");
			break;
		case 1:
			objectSprite = LoadTexture("Sprites/tv.png");
			break;
	}
}

void TransObject::Draw()
{
	if(!isPickedUp)
		DrawTextureV(objectSprite, position, WHITE);
	else
		DrawTextureV(objectSprite, goalPos, Color{ 255, 255, 255, 100 });
	DrawLineV(position, goalPos, RED);
}

bool TransObject::Collision(Rectangle playerRect, bool isTransformed)
{
	if (!isTransformed)
		return CheckCollisionRecs(GetRect(), playerRect);
	else
		return false;
}

Rectangle TransObject::GetRect()
{
	return Rectangle{ position.x, position.y, float(objectSprite.width), float(objectSprite.height) };
}
