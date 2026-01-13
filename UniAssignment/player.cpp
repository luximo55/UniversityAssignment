#include "player.hpp"
#include <iostream>
using namespace std;

Player::Player()
{
	activeSprite = LoadTexture("Sprites/player.png");
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

void Player::Update(bool isColliding)
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

	if (IsKeyReleased(KEY_SPACE) && isColliding)
	{

	}
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
