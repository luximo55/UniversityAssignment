using namespace std;
#include <list>
#include <memory>
#include <math.h>
#include <iostream>
#include "raylib.h"
#include "player.hpp"
#include "transObject.hpp"

list<shared_ptr<TransObject>> InitializeObjects()
{
	auto table = make_shared<TransObject>(0, 650, 100, 400, 550);
	auto tv = make_shared<TransObject>(1, 100, 450, 450, 300);
	list<shared_ptr<TransObject>> transObjects = { table, tv };
	return transObjects;
}

bool CheckPlace(shared_ptr<TransObject> to)
{
	if (abs(to->position.x - to->goalPos.x) <= 15 && abs(to->position.x - to->goalPos.x) >= 0)
	{
		to->position = to->goalPos;
		return false;
	}
	return true;
}

int main()
{
	InitWindow(1024, 768, "BUas Project");
	SetTargetFPS(60);

	Vector2 position;
	position.x = 500;
	position.y = 200;
	Player player;
	list<shared_ptr<TransObject>> transObjects = InitializeObjects();

	// --Game loop--
	while(WindowShouldClose() == false)
	{
		// --Events--
		bool isColliding;
		for (shared_ptr<TransObject> to : transObjects)
		{
			if (to->Collision(player.GetRect(), player.isTransformed) && to->pickupable)
			{
				isColliding = true;
				if (IsKeyReleased(KEY_SPACE) && !player.isTransformed) 
				{
					player.SpriteChange(to->objectSprite, isColliding);
					player.position = to->position;
					to->isPickedUp = true;
					player.isTransformed = true;
				}
				break;
			}
			else
			{
				isColliding = false;
				if (IsKeyReleased(KEY_SPACE) && player.isTransformed && to->isPickedUp)
				{
					player.SpriteChange(to->objectSprite, isColliding);
					to->position = player.position;
					player.isTransformed = false;
					to->pickupable = CheckPlace(to);
				}
			}
			if (!player.isTransformed)
			{
				to->isPickedUp = false;
			}
		}
		player.Update();		

		// --Drawing--
		BeginDrawing();
		{
			//System Drawing
			ClearBackground(DARKBROWN);
			DrawFPS(0, 0);


			//Playable elements

			for (shared_ptr<TransObject> to : transObjects)
			{
				to->Draw();
			}
			player.Draw();
			player.DrawHitBox(isColliding);
			
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}