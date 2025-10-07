#include "ScreenTitle.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"

ScreenTitleState& ScreenTitleState::getInstance()
{
	static ScreenTitleState singleton;
	return singleton;
}


void ScreenTitleState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	alphaIncrease = 0.01f;
	alpha = 0;
	state = 0;

	TraceLog(LOG_INFO, "ScreenTitleState::InitScreen");

	// Use this to access to the Game instance
	GameManager& GameInst = GameManager::GetGameManager();
	
	// Loading Texture2D and initial positions
	Image titleImage = LoadImage("resources/Menu/MainLogo.png");
	title = LoadTextureFromImage(titleImage);
	UnloadImage(titleImage);

	titlex = GetScreenWidth() / 2 - title.width / 2;
	titley = 30;
	
}

void ScreenTitleState::UpdateScreen(float deltaTime)
{
	GameManager& GameInst = GameManager::GetGameManager();

	framesCounter++;

	if (state == 0)
	{
		if (framesCounter == ANIM_DURATION) {
			state = 1;
			framesCounter = 0;
		}
	}
	else if (state == 1)
	{
		alpha += alphaIncrease;
		if (alpha >= 1.00f || alpha <= 0.00f)
		{
			alphaIncrease *= -1;
		}
	}


	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 2;   // GAMEPLAY
	}

	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // OPTIONS
	}
}

void ScreenTitleState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);		// Background
	GameManager& GameInst = GameManager::GetGameManager();

	if (state == 0)			// Tittle Animation
	{
		DrawTexture(title, titlex, GetScreenHeight() -(GetScreenHeight()-titley)*framesCounter/ANIM_DURATION, WHITE);		// Anim interpolation
	}
	else if (state == 1)	// After title animation
	{
		DrawTexture(title, titlex, titley, WHITE);

		float posx = ((GetScreenWidth() / 2.f) - (MeasureText("by Laura I.", 20) / 2.f));
		DrawTextEx(GameInst.GetFont(), " by Laura I.", Vector2{ posx, 450.f }, 20, 4, WHITE);

		posx = ((GetScreenWidth() / 2.f) - (MeasureText("Press Enter for Playing", 20) / 2.f));
		DrawTextEx(GameInst.GetFont(InportedFontType::PIXEL), "PRESS ENTER FOR PLAYING", Vector2{ posx,500.f }, 25,4, Fade(WHITE, alpha));

		//DrawText("Press Enter for Playing", (GetScreenWidth() / 2) - (MeasureText("Press Enter for Playing", 25) / 2), 500, 25, Fade(WHITE,alpha));
		DrawText("Press 'O' for Instructions", (GetScreenWidth() / 2) - (MeasureText("Press 'O' for Instructions", 25) / 2), 560, 25, WHITE);
	}
}

void ScreenTitleState::UnloadScreen(void)
{
	GameManager& GameInst = GameManager::GetGameManager();

}

int ScreenTitleState::FinishScreen(void)
{
	return finishScreen;
}