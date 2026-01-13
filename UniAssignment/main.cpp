#include "raylib.h"
#include "player.hpp"
#include "transObject.hpp"


int main()
{
	InitWindow(1024, 768, "BUas Project");
	SetTargetFPS(60);

	Vector2 position;
	position.x = 500;
	position.y = 200;
	Vector2 altPos;
	altPos.x = 100;
	altPos.y = 500;
	Player player;
	TransObject table(0, 650, 100);
	TransObject tv(1, 100, 450);

	while(WindowShouldClose() == false)
	{
		// --Events--
		bool isColliding;
		if (table.Collision(player.GetRect()) || tv.Collision(player.GetRect()))
			isColliding = true;
		else
			isColliding = false;
		player.Update(isColliding);

		// --Positions--

		// --Drawing--
		BeginDrawing();
		{
			//System Drawing
			ClearBackground(DARKBROWN);
			DrawFPS(0, 0);


			//Playable elements

			table.Draw();
			tv.Draw();
			player.Draw();
			player.DrawHitBox(isColliding);
			
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}