#include "transObject.hpp"

TransObject::TransObject(int choice, int posX, int posY)
{
	TexturePick(choice);
	isPickedUp = false;
	position.x = posX;
	position.y = posY;
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

void TransObject::Draw(bool isPickedUp)
{
	if(!isPickedUp)
		DrawTextureV(objectSprite, position, WHITE);
}

bool TransObject::Collision(Rectangle playerRect)
{
	if (!isPickedUp)
		return CheckCollisionRecs(GetRect(), playerRect);
	else
		return false;
}

Rectangle TransObject::GetRect()
{
	return Rectangle{ position.x, position.y, float(objectSprite.width), float(objectSprite.height) };
}
