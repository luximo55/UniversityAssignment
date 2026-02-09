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
	auto table = make_shared<TransObject>(0, 650, 100, 400, 550);
	auto tv = make_shared<TransObject>(1, 100, 450, 450, 300);
	auto desk = make_shared<TransObject>(2, 231, 412, 457, 635);
	auto closet = make_shared<TransObject>(3, 742, 432, 342, 600);
	auto bed = make_shared<TransObject>(4, 900, 600, 231, 311);
	list<shared_ptr<TransObject>> transObjects = { table, tv, desk, closet, bed};
	return transObjects;
}

//Checking if the position of object being placed is correct to the final goal position of the object
bool CheckPlace(shared_ptr<TransObject> to)
{
	if (abs(to->position.x - to->goalPos.x) <= 35 && abs(to->position.x - to->goalPos.x) >= 0)
	{
		to->position = to->goalPos;
		return false;
	}
	return true;
}

int main()
{
	//Window initialization
	InitWindow(1024, 768, "BUas Project");
	SetTargetFPS(60);
	
	//Graphics
	Texture2D background = LoadTexture("Sprites/Background/background.png");
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;
	char timeChar[4];
	char scoreText[5];
	const char* goText = "Game over";
	const char* restartText = "Press 'R' to try again";

	//Objects
	Player player;
	list<shared_ptr<TransObject>> transObjects = InitializeObjects();
	
	//Logic - time, score
	double timeCountdown = 20;
	double currentTime = GetTime() + timeCountdown;
	bool gamePause = false;
	int points = 0;	
	
	//Audio
	Audio audio;

	// --Game loop--
	while(WindowShouldClose() == false)
	{
		// --Events--
		bool isColliding;

		//Check game state before calculation
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
			currentTime = GetTime() + 20;
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
		{
			audio.PlayAudio();
		}

		// --Drawing--
		BeginDrawing();
		{
			//Background
			DrawTextureEx(background, zero, 0, 4, WHITE);

			//Playable elements
			//Drawing the player and objects
			for (shared_ptr<TransObject> to : transObjects)
			{
				to->Draw();
			}
			player.Draw();
			player.DrawHitBox(isColliding);

			//System Drawing
			ClearBackground(DARKBROWN);
			
			//Countdown
			snprintf(timeChar, sizeof timeChar, "%.3f", timeCountdown);
			DrawText(timeChar, 70, 0, 64, WHITE);
			
			//Drawing of the gameover screen
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