#include "transObject.hpp"
using namespace std;

TransObject::TransObject(string choice, int posX, int posY, int goalX, int goalY)
{
	spritePath = "Sprites/";
	isPickedUp = false;
	pickupable = true;
	position.x = posX;
	position.y = posY;
	goalPos.x = goalX;
	goalPos.y = goalY;
	spriteScale = 8;
	TexturePick(choice);
}

TransObject::~TransObject()
{
	UnloadTexture(objectSprite);
}

//Allocates three sprites (that represent its state) to an object being initialized
//Makes combination for sprite paths e.g. Sprites/Table/wreck.png
void TransObject::TexturePick(string choice)
{
	spritePath.insert(spritePath.size(), choice);
	int pathSizeIndex = spritePath.size();
	
	sprite = spritePath.insert(spritePath.size(), "/wreck.png").c_str();
	wreckSprite = LoadTexture(sprite);
	//erase is used to reset to the path of sprites e.g. Sprites/Table/wreck.png -> Sprites/Table
	spritePath.erase(pathSizeIndex, 10);
	//then another sprite is added to the path
	sprite = spritePath.insert(spritePath.size(), "/ghost.png").c_str();
	ghostSprite = LoadTexture(sprite);
	spritePath.erase(pathSizeIndex, 10);

	sprite = spritePath.insert(spritePath.size(), "/clean.png").c_str();
	cleanSprite = LoadTexture(sprite);
}

//Draws a specific object sprite depening on the state of the object
/*States: wrecked and not picked up; clean and not pickupable (it has been placed in the correct place);
clean and picked up (a ghost of the object as goal position, the player is transformed into the object)*/
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
}

//Collision check for transforming into the object
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
