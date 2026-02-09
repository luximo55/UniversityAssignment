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
	spriteScale = 6;
}

TransObject::~TransObject()
{
	UnloadTexture(objectSprite);
}

//Allocates three sprites (that represent its state) to an object being initialized
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
		case 2:
			wreckSprite = LoadTexture("Sprites/Desk/wreck.png");
			ghostSprite = LoadTexture("Sprites/Desk/ghost.png");
			cleanSprite = LoadTexture("Sprites/Desk/clean.png");
			objectSprite = wreckSprite;
			break;
		case 3:
			wreckSprite = LoadTexture("Sprites/Closet/wreck.png");
			ghostSprite = LoadTexture("Sprites/Closet/ghost.png");
			cleanSprite = LoadTexture("Sprites/Closet/clean.png");
			objectSprite = wreckSprite;
			break;
		case 4:
			wreckSprite = LoadTexture("Sprites/Bed/wreck.png");
			ghostSprite = LoadTexture("Sprites/Bed/ghost.png");
			cleanSprite = LoadTexture("Sprites/Bed/clean.png");
			objectSprite = wreckSprite;
			break;
	}
}

//Draws a specific sprite depening on the state of the object
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

//Check if there is collision with the player
bool TransObject::Collision(Rectangle playerRect, bool isTransformed)
{
	if (!isTransformed)
		return CheckCollisionRecs(GetRect(), playerRect);
	else
		return false;
}

//Calculates the rect dimensions 
Rectangle TransObject::GetRect()
{
	return Rectangle{ position.x, position.y, float(objectSprite.width*spriteScale), float(objectSprite.height*spriteScale) };
}
