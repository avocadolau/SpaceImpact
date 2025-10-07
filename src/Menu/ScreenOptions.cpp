#include "ScreenOptions.h"
#include "raylib.h"

#include "Game/GlobalGameDefines.h"


ScreenOptionsState::ScreenOptionsState()
{

}

ScreenOptionsState& ScreenOptionsState::getInstance()
{
	static ScreenOptionsState singleton;
	return singleton;
}

void ScreenOptionsState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
}

void ScreenOptionsState::UpdateScreen(float deltaTime)
{
	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // TITLE
	}
}

void ScreenOptionsState::DrawScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    const char* line1 = "To move PLAYER use the direction keys or A,D,W,S.";
    const char* line2 = "PLAYER has 3 lives, loose 1 each time you get hit";
    const char* line3 = "kill enemies to earn points";
    const char* line4 = "each enemy type has different stats";
    const char* line5 = "To win PLAYER has to defeat the BOSS.";
    const char* line6 = "You loose if you run out of lives.";

    DrawText(line1, (GetScreenWidth() / 2) - (MeasureText(line1, 20) / 2.), 150, 20, WHITE);
    DrawText(line2, (GetScreenWidth() / 2) - (MeasureText(line2, 20) / 2.), 180, 20, WHITE);
    DrawText(line3, (GetScreenWidth() / 2) - (MeasureText(line3, 20) / 2.), 210, 20, WHITE);
    DrawText(line4, (GetScreenWidth() / 2) - (MeasureText(line4, 20) / 2.), 240, 20, WHITE);
    DrawText(line5, (GetScreenWidth() / 2) - (MeasureText(line5, 20) / 2.), 270, 20, WHITE);
    DrawText(line6, (GetScreenWidth() / 2) - (MeasureText(line6, 20) / 2.), 300, 20, WHITE);

    const char* line7 = "Press 'O' to return to Title.";

    DrawText(line7, (GetScreenWidth() / 2.f) - (MeasureText(line7, 20) / 2.), 380, 20, WHITE);
}

void ScreenOptionsState::UnloadScreen(void)
{

}

int ScreenOptionsState::FinishScreen(void)
{
	return finishScreen;
}