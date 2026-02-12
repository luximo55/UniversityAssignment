using namespace std;
#include <list>
#include <memory>
#include <math.h>
#include <string>
#include <iostream>
#include "raylib.h"
#include "player.hpp"
#include "transObject.hpp"
#include "audio.hpp"

//initializes all objects into a list
list<shared_ptr<TransObject>> InitializeObjects()
{
	auto table = make_shared<TransObject>("Table", 630, 496, 0, 496);
	auto tv = make_shared<TransObject>("TV", 415, 240, 885, 624);
	auto desk = make_shared<TransObject>("Desk", 655, 112, 40, 112);
	auto closet = make_shared<TransObject>("Closet", 400, 496, 650, 112);
	auto bed = make_shared<TransObject>("Bed", 40, 624, 775, 240);
	auto couch = make_shared<TransObject>("Couch", 65, 240, 640, 624);
	auto chair1 = make_shared<TransObject>("Chair", 890, 112, 230, 495);
	auto chair2 = make_shared<TransObject>("Chair", 875, 496, 175, 112);
	list<shared_ptr<TransObject>> transObjects = { table, tv, desk, closet, bed, couch, chair1, chair2};
	return transObjects;
}

//Checking if the position of the object being placed is close to its goal position
bool CheckPlace(shared_ptr<TransObject> to)
{
	if (abs(to->position.x - to->goalPos.x) <= 30 && abs(to->position.y - to->goalPos.y) <= 40)
	{
		to->position = to->goalPos;
		return false;
	}
	return true;
}

int main()
{
	// --Window initialization--
	InitWindow(1024, 768, "BUas Project");
	SetTargetFPS(60);
	
	// --Graphics--
	Texture2D background = LoadTexture("Sprites/Background/background.png");
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;
	char timeChar[4];
	char scoreText[5];
	const char* goText = "Game over";
	const char* restartText = "Press 'R' to try again";

	// --Objects--
	Player player;
	list<shared_ptr<TransObject>> transObjects = InitializeObjects();
	
	// --Logic - time, score--
	double timeCountdown = 50;
	double currentTime = GetTime() + timeCountdown;
	bool gamePause = false;
	int points = 0;	
	
	// --Audio--
	Audio audio;

	// --Game loop--
	while(WindowShouldClose() == false)
	{
		// --Events--
		bool isColliding;

		if (!player.gameover)
		{
			//Checking collision of each object
			for (shared_ptr<TransObject> to : transObjects)
			{
				//Checking if the object has collided with player, and is able to be picked up
				if (to->Collision(player.GetRect(), player.isTransformed) && to->pickupable)
				{
					isColliding = true;
					//Allows the object to be picked up by setting object's ghost sprite as players active sprite
					if (IsKeyReleased(KEY_SPACE) && !player.isTransformed)
					{
						audio.PlaySFX(audio.transIn);
						player.SpriteChange(to->ghostSprite, isColliding);
						player.position = to->position;
						to->isPickedUp = true;
						player.isTransformed = true;
					}
					break;
				}
				else
				{
					isColliding = false;
					//Drop the object, and check if it's in the correct position, if so lock it and add points
					if (IsKeyReleased(KEY_SPACE) && player.isTransformed && to->isPickedUp)
					{
						audio.PlaySFX(audio.transOut);
						player.SpriteChange(to->objectSprite, isColliding);
						to->position = player.position;
						player.isTransformed = false;
						to->pickupable = CheckPlace(to);
						if (to->pickupable == false)
							points++;
					}
				}
				if (!player.isTransformed)
					to->isPickedUp = false;
			}
		}
		player.Update();

		//Game over condition
		if (IsKeyReleased(KEY_T) || timeCountdown <= 0 || points >= transObjects.size())
			player.gameover = true;
		
		//Game over sequence (Displays the gameover screen)
		if (player.gameover && !gamePause)
		{
			if (points >= transObjects.size())
				audio.PlaySFX(audio.win);
			else
				audio.PlaySFX(audio.lose);
			double score = 0.1;
			score = trunc((timeCountdown + 1) * 100 * (points * 2));
			gamePause = true;
			cout << "gameover ";
			snprintf(scoreText, sizeof scoreText, "%.0f", score);
			timeCountdown = 0.01;
		}
		//Time countdown
		else if(!player.gameover && !gamePause)
			timeCountdown = currentTime - GetTime();

		//Game reset
		if (IsKeyReleased(KEY_R) && gamePause && player.gameover)
		{
			currentTime = GetTime() + 50;
			transObjects.clear();
			transObjects = InitializeObjects();
			player.gameover = false;
			player.isTransformed = false;
			player.activeSprite = player.playerSprite;
			player.position.x = 100;
			player.position.y = 100;
			isColliding = false;
			gamePause = false;
			points = 0;
		}

		// --Audio Playback--
		if (!IsSoundPlaying(audio.music))
			audio.PlayAudio();

		// --Drawing--
		BeginDrawing();
		{
			//Background
			DrawTextureEx(background, zero, 0, 8, WHITE);

			//Playable elements
			//Drawing the player and objects
			for (shared_ptr<TransObject> to : transObjects)
			{
				to->Draw();
			}
			player.Draw();

			//Remove this-------------------------------------------------------------------------------------<
			char bufX[10];
			snprintf(bufX, sizeof bufX, "%.0f", player.position.x);
			DrawText(bufX, 500,0,30,RED);
			char bufY[10];
			snprintf(bufY, sizeof bufY, "%.0f", player.position.y);
			DrawText(bufY, 600, 0, 30, RED);

			//System Drawing
			ClearBackground(DARKBROWN);
			
			//Countdown
			snprintf(timeChar, sizeof timeChar, "%.3f", timeCountdown);
			DrawText(timeChar, 70, 0, 64, WHITE);
			
			//Drawing of the gameover screen
			if (player.gameover)
			{
				DrawText(goText, GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), goText, 100, 10).x / 2, 50, 100, GOLD);
				DrawText(scoreText, GetScreenWidth()/2 - MeasureTextEx(GetFontDefault(), scoreText, 100, 10).x/2, 150, 100, GOLD);
				DrawText(restartText, GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), restartText, 70, 7).x / 2, 670, 70, GOLD);
			}

		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}