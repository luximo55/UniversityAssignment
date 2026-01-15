#include "player.hpp"
#include <iostream>
using namespace std;

Player::Player()
{
	playerSprite = LoadTexture("Sprites/player.png");
	activeSprite = playerSprite;
	position.x = 100;
	position.y = 100;
	speed = 5;
}

Player::~Player()
{
	UnloadTexture(activeSprite);
}

void Player::Draw()
{
	DrawTextureV(activeSprite, position, WHITE);
}

void Player::Update()
{
	if (IsKeyDown(KEY_RIGHT))
	{
		position.x += speed;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		position.x -= speed;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		position.y += speed;
	}
	else if (IsKeyDown(KEY_UP))
	{
		position.y -= speed;
	}
}

void Player::SpriteChange(Texture2D objectTexture, bool isColliding)
{
	if (isColliding)
		activeSprite = objectTexture;
	else
		activeSprite = playerSprite;
}

Rectangle Player::GetRect()
{
	return Rectangle{position.x, position.y, float(activeSprite.width), float(activeSprite.height)};
}

void Player::DrawHitBox(bool isColliding)
{
	if (isColliding)
		DrawRectangleLinesEx(GetRect(), 3, RED);
}
