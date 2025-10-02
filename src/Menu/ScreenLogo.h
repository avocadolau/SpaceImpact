#pragma once
#include "StateMachineMngr.h"
#include "raylib.h"

#define WIP_LOGO

class ScreenLogoState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};


	void InitScreen(void);
	void UpdateScreen(float deltaTime);
	void DrawScreen(void);
	void UnloadScreen(void);
	int FinishScreen(void);
	
	int getScreenId() { return (int)ScreenState::LOGO; }


	static ScreenLogoState& getInstance();

private:
	ScreenLogoState();
	ScreenLogoState(const ScreenLogoState& other);
	ScreenLogoState& operator= (const ScreenLogoState& other);

	int chargeTime_;

	int framesCounter = 0;
	int finishScreen = 0;

	int logoPositionX = 0;
	int logoPositionY = 0;


	int state = 0;              // Logo animation states
	float alpha = 0.0f;         // Useful for fading

	const char* text;
	int textCount;
	Texture2D logoTex;
};