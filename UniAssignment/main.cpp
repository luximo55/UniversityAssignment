using namespace std;
#include <list>
#include <memory>
#include "raylib.h"
#include "player.hpp"
#include "transObject.hpp"

list<shared_ptr<TransObject>> InitializeObjects()
{
	auto table = make_shared<TransObject>(0, 650, 100);
	auto tv = make_shared<TransObject>(1, 100, 450);
	list<shared_ptr<TransObject>> transObjects = { table, tv };	
	return transObjects;
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
			if (to->Collision(player.GetRect()))
			{
				isColliding = true;
				if (IsKeyReleased(KEY_SPACE))
					player.SpriteChange(to->objectSprite, isColliding);
				break;
			}
			else
			{
				isColliding = false;
				if (IsKeyReleased(KEY_SPACE))
					player.SpriteChange(to->objectSprite, isColliding);
			}
		}
		player.Update();

		// --Positions--

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