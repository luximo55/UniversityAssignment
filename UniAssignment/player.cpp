#include "player.hpp"
#include <iostream>
using namespace std;

Player::Player()
{
	playerSprite = LoadTexture("Sprites/Ghost/Ghost.png");
	activeSprite = playerSprite;
	isTransformed = false;
	gameover = false;
	position.x = 100;
	position.y = 100;
	speed = 5;
	spriteScale = 5;
}

Player::~Player()
{
	UnloadTexture(activeSprite);
}

//Draws player's texture
void Player::Draw()
{
	DrawTextureEx(activeSprite, position, 0, spriteScale, WHITE);
}

//Checks user input for movement 
void Player::Update()
{
	if(!gameover)
	{
		if (IsKeyDown(KEY_RIGHT))
			position.x += speed;
		else if (IsKeyDown(KEY_LEFT))
			position.x -= speed;
		if (IsKeyDown(KEY_DOWN))
			position.y += speed;
		else if (IsKeyDown(KEY_UP))
			position.y -= speed;
	}
}

//Changes player's sprite if the player has transformed
void Player::SpriteChange(Texture2D ghostTexture, bool isColliding)
{
	if (isColliding)
		activeSprite = ghostTexture;
	else
		activeSprite = playerSprite;
}

//Calculates the dimensions of the rect
Rectangle Player::GetRect()
{
	return Rectangle{position.x, position.y, float(activeSprite.width*spriteScale), float(activeSprite.height*spriteScale)};
}

//Visualizes the rect around player
void Player::DrawHitBox(bool isColliding)
{
	if (isColliding)
		DrawRectangleLinesEx(GetRect(), 3, RED);
}
