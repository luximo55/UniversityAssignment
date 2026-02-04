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
	spriteScale = 5;
}

TransObject::~TransObject()
{
	UnloadTexture(objectSprite);
}

void TransObject::ReinitializeObjects()
{

}

void TransObject::TexturePick(int choice)
{
	switch (choice)
	{
		case 0:
			wreckSprite = LoadTexture("Sprites/Table/wreck.png");
			ghostSprite = LoadTexture("Sprites/Table/ghost.png"); 
			cleanSprite = LoadTexture("Sprites/Table/clean.png");
			objectSprite = wreckSprite;
			break;
		case 1:
			wreckSprite = LoadTexture("Sprites/TV/wreck.png");
			ghostSprite = LoadTexture("Sprites/TV/ghost.png");
			cleanSprite = LoadTexture("Sprites/TV/clean.png");
			objectSprite = wreckSprite;
			break;
	}
}

void TransObject::Draw()
{
	if (!isPickedUp && pickupable)
	{
		objectSprite = wreckSprite;
		DrawTextureEx(objectSprite, position, 0, spriteScale, WHITE);
	}
	else if (!pickupable)
	{
		objectSprite = cleanSprite;
		DrawTextureEx(objectSprite, position, 0, spriteScale, WHITE);
	}
	else if (isPickedUp)
	{
		objectSprite = cleanSprite;
		DrawTextureEx(objectSprite, goalPos, 0, spriteScale, Color{ 255, 255, 255, 100 });
	}
	//DrawLineV(position, goalPos, RED);
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
	return Rectangle{ position.x, position.y, float(objectSprite.width*spriteScale), float(objectSprite.height*spriteScale) };
}
