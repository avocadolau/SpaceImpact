
#pragma once
#include "StateMachineMngr.h"
#include "Screen.h"
#include "raylib.h"

#define ANIM_DURATION 60

class ScreenTitleState : public StateMachineMngr
{
public:

	void enter(Screen* screen){}
	void toggle(Screen* screen){};
	void exit(Screen* screen){};

	void InitScreen(void);
	void UpdateScreen(float deltaTime);
	void DrawScreen(void);
	void UnloadScreen(void);
	int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::TITLE; }

	static ScreenTitleState& getInstance();

private:

	ScreenTitleState(){};
	ScreenTitleState(const ScreenTitleState& other);
	ScreenTitleState& operator= (const ScreenTitleState& other);

	int framesCounter = 0;
	int finishScreen = 0;

	int state;		// Title animation states
	Texture2D title;

	int titlex;
	int titley;
	float alpha;
	float alphaIncrease;

};