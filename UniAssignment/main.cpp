using namespace std;
#include <list>
#include <memory>
#include <math.h>
#include <string>
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
	if (abs(to->position.x - to->goalPos.x) <= 25 && abs(to->position.x - to->goalPos.x) >= 0)
	{
		to->position = to->goalPos;
		return false;
	}
	return true;
}

void EndState(int score)
{
}

int main()
{
	InitWindow(1024, 768, "BUas Project");
	SetTargetFPS(60);

	Player player;
	list<shared_ptr<TransObject>> transObjects = InitializeObjects();
	double timeCountdown = 100;
	double currentTime = GetTime() + 10;
	char timeChar[4];
	char scoreText[5];
	const char* goText = "Game over";
	const char* restartText = "Press 'R' to try again";
	bool gamePause = false;
	int points = 0;

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
					if (to->pickupable == false)
						points++;
				}
			}
			if (!player.isTransformed)
			{
				to->isPickedUp = false;
			}
		}
		if (IsKeyReleased(KEY_T))
			player.gameover = true;
		player.Update();
		if ((timeCountdown <= 0 || player.gameover) && !gamePause)
		{
			if (!player.gameover)
				player.gameover = true;
			double score = 0.1;
			score = trunc((timeCountdown + 1) * 100 * (points * 2));
			gamePause = true;
			cout << "gameover ";
			snprintf(scoreText, sizeof scoreText, "%.0f", score);
			EndState(score);
		}
		else if(!player.gameover && !gamePause)
		{
			timeCountdown = currentTime - GetTime();
		}
		if (IsKeyReleased(KEY_R) && gamePause && player.gameover)
		{
			transObjects.clear();
			transObjects = InitializeObjects();
			player.gameover = false;
			player.isTransformed = false;
			player.position.x = 100;
			player.position.y = 100;
			isColliding = false;
			gamePause = false;
			currentTime = GetTime() + 10;
			points = 0;
		}

		// --Drawing--
		BeginDrawing();
		{
			//Playable elements

			for (shared_ptr<TransObject> to : transObjects)
			{
				to->Draw();
			}
			player.Draw();
			player.DrawHitBox(isColliding);

			//System Drawing
			ClearBackground(DARKBROWN);
			DrawFPS(0, 0);
			snprintf(timeChar, sizeof timeChar, "%.3f", timeCountdown);
			DrawText(timeChar, 100, 0, 20, GREEN);

			if (player.gameover)
			{
				DrawText(goText, GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), goText, 100, 10).x / 2, 50, 100, GREEN);
				DrawText(scoreText, GetScreenWidth()/2 - MeasureTextEx(GetFontDefault(), scoreText, 100, 10).x/2, 150, 100, GREEN);
				DrawText(restartText, GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), restartText, 70, 7).x / 2, 600, 70, GREEN);
			}

		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}