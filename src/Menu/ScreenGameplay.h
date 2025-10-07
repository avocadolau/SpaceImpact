#pragma once

#include <vector>

#include "StateMachineMngr.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Shoot.h"
#include "Game/Entities/Enemy.h"

#define SPAWN_RATE 90

class ScreenGameplayState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};

	virtual void InitScreen(void);
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen(void);
	virtual void UnloadScreen(void);
	virtual int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::GAMEPLAY; }

	static ScreenGameplayState& getInstance();

private:
	ScreenGameplayState();
	ScreenGameplayState(const ScreenGameplayState& other);
	ScreenGameplayState& operator= (const ScreenGameplayState& other);

	void SpawnEnemies();
	void CheckCollisions();
	void EvaluateInput();

	void DebugOptions();
	void DrawDebug();

	int framesCounter = 0;
	int finishScreen = 0;
	bool mb_ReplayLevel = false;

	bool debug_floor = false;
	bool debug_stairs = false;

	int shootCooldown = 0;
	int enemiesSpawnState = 0;

	Texture2D landscape;
	Texture2D heart;
	
	Player* player = nullptr;
	Boss* boss = nullptr;
	std::vector<Entity*> entities;
	bool matrix[CollisionType::MAX][CollisionType::MAX];
};