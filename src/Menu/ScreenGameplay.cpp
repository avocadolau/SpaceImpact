
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"

#include <string>


ScreenGameplayState::ScreenGameplayState()
{

}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	Image landscapeImg = LoadImage("resources/Game/Landscape.png");
	landscape = LoadTextureFromImage(landscapeImg);
	UnloadImage(landscapeImg);
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();

	// Controlls

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 2;   // GAMEPLAY
	}

	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // OPTIONS
	}

	// Update all entities


	// check collisions


}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	GameManager& GameInst = GameManager::GetGameManager();

	// Landscape
	DrawTexture(landscape, GetScreenWidth() / 2 - landscape.width / 2, GetScreenHeight() / 2 - landscape.height / 2, WHITE);

	// Entities

	
	// UI Score, lives

	Font font = GameInst.GetFont();

	DrawText("SCORE:", 300.f, 100.f, 25, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);


}

void ScreenGameplayState::UnloadScreen(void)
{

}

int  ScreenGameplayState::FinishScreen(void)
{
	return finishScreen;
}

void ScreenGameplayState::EvaluateInput()
{

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 4;   // END SCREEN
	}
}

void ScreenGameplayState::DebugOptions()
{

}

void ScreenGameplayState::DrawDebug()
{
	GameManager& GameInst = GameManager::GetGameManager();

}