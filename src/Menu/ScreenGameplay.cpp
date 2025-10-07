
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"

#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"
#include "Game/Entities/Entity.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Shoot.h"
#include "Game/Entities/Enemy.h"

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
	enemiesSpawnState = 0;

	// Loading Images
	Image image = LoadImage("resources/Game/Landscape.png");
	landscape = LoadTextureFromImage(image);
	UnloadImage(image);
	image = LoadImage("resources/Game/LivesIcon.png");
	heart = LoadTextureFromImage(image);
	UnloadImage(image);

	// Init entities
	Vector2 playerPos;
	playerPos.x = (GetScreenWidth() / 2 - landscape.width / 2) + 10;
	playerPos.y = GetScreenHeight() / 2;
	
	player = new Player(playerPos);
	boss = nullptr;
	entities.push_back(player);

	// setting collision conditions
	matrix[PLAYER][PLAYER] = false;
	matrix[PLAYER][PROJECTILE] = true;
	matrix[PLAYER][ENEMY] = true;

	matrix[PROJECTILE][PLAYER] = true;
	matrix[PROJECTILE][PROJECTILE] = true;
	matrix[PROJECTILE][ENEMY] = true;

	matrix[ENEMY][PLAYER] = true;
	matrix[ENEMY][PROJECTILE] = true;
	matrix[ENEMY][ENEMY] = false;

	// play sound
	GameManager::GetGameManager().Play(GameManager::START_GAME);
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();

	// Controlls
	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) finishScreen = 2;	// GAMEPLAY
	if (IsKeyPressed(KEY_O)) finishScreen = 1;											// OPTIONS

	if (IsKeyDown(KEY_SPACE) && shootCooldown == 0) {									// Shoot
		Shoot* p = new Shoot({ player->GetRec().x + player->GetRec().width,player->GetRec().y + player->GetRec().height / 2 }, Shoot::ShootDirection::R);
		entities.push_back(p);
		shootCooldown = 30;
		GameManager::GetGameManager().Play(GameManager::SHOOT);
	}
	if (shootCooldown > 0) shootCooldown--;

	// EnemySpawn
	framesCounter++;
	SpawnEnemies();

	// Update all entities
	for (Entity* entity : entities)
		if (entity->IsActive()) entity->Update();
	CheckCollisions();
}

void ScreenGameplayState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	GameManager& GameInst = GameManager::GetGameManager();

	// Landscape
	DrawTexture(landscape, GetScreenWidth() / 2 - landscape.width / 2, GetScreenHeight() / 2 - landscape.height / 2, WHITE);

	// Entities
	for (Entity* e : entities)
		if (e->IsActive()) e->Draw();
	
	// UI Score, lives
	for (int i = 0; i < GameInst.GetLives(); i++) DrawTexture(heart, 80 + i * (heart.width + 20), 20, WHITE);

	Font font = GameInst.GetFont();
	DrawText("SCORE:", 400.f, 35.f, 25, LIGHTGREEN);
	DrawText(to_string(GameInst.GetScore()).c_str(), 540.f, 35.f, 25, LIGHTGREEN);
}

void ScreenGameplayState::UnloadScreen(void)
{
	// delete all entities
	Entity* e;
	for (int i = entities.size() - 1; i >= 0; i--) {
		e = entities.at(i);
		delete e;
	}
	entities.clear();
}

int  ScreenGameplayState::FinishScreen(void)
{
	bool finish = false;

	// Win & Lose Condition
	if (boss) if (!boss->IsActive()) {
		finishScreen = 4;
		boss = nullptr;
	}
	if (GameManager::GetGameManager().GetLives() < 0) finishScreen = 4;

	// check entities to delete
	for (int i = entities.size()-1; i >= 0; i--) {
		Entity* e = entities.at(i);
		if (!e->IsActive()) {
			delete e;
			entities.at(i) = nullptr;
			auto it= std::find(entities.begin(), entities.end(), nullptr);
			entities.erase(it);
		}
	}
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

void ScreenGameplayState::SpawnEnemies() {
	if (enemiesSpawnState == 0) {				// Spawning Enemy_1
		if (framesCounter > SPAWN_RATE * 5) {
			framesCounter = 0;
			enemiesSpawnState = 1;
		}
		else if (framesCounter % SPAWN_RATE == 0) {
			Vector2 newPos;
			newPos.x = GetScreenWidth();
			newPos.y = GetRandomValue(90, GetScreenHeight() - 60);
			Enemy* nEnemy = new Enemy(newPos, Enemy::ENEMY_1);
			entities.push_back(nEnemy);
		}
	}
	else if (enemiesSpawnState == 1) {				// Spawning Enemy_2
		if (framesCounter > SPAWN_RATE * 4) {
			framesCounter = 0;
			enemiesSpawnState = 2;
		}
		else if (framesCounter % SPAWN_RATE == 0) {
			Vector2 newPos;
			newPos.x = GetScreenWidth();
			newPos.y = GetRandomValue(90, GetScreenHeight() - 60);
			Enemy* nEnemy = new Enemy(newPos, Enemy::ENEMY_2);
			entities.push_back(nEnemy);
		}
	}
	else if (enemiesSpawnState == 2) {				// Spawning Enemy_2
		if (framesCounter > SPAWN_RATE * 4) {
			framesCounter = 0;
			enemiesSpawnState = 3;
		}
		else if (framesCounter % SPAWN_RATE == 0) {
			Vector2 newPos;
			newPos.x = GetScreenWidth();
			newPos.y = GetRandomValue(90, GetScreenHeight() - 60);
			Enemy* nEnemy = new Enemy(newPos, Enemy::ENEMY_3);
			entities.push_back(nEnemy);
		}
	}
	else if (enemiesSpawnState == 3) {				// Spawning Boss
		if (boss) {
			if (boss->shoot) enemiesSpawnState = 4;
		}
		else if (framesCounter % SPAWN_RATE == 0) {
			Vector2 newPos;
			newPos.x = GetScreenWidth();
			newPos.y = GetRandomValue(90, GetScreenHeight() - 250);
			boss = new Boss(newPos);
			entities.push_back(boss);
		}
	}
	else if (enemiesSpawnState == 4) {				// Spawning Enemy Shoots
		if (boss) {
			if (boss->IsActive() && framesCounter % 40 == 0) {
				Shoot* p = new Shoot({ boss->GetRec().x - 50, boss->GetRec().y + boss->GetRec().height / 2 }, Shoot::L);
				entities.push_back(p);
			}
		}
		else enemiesSpawnState = 5;
	}
}

void ScreenGameplayState::CheckCollisions() {
	Entity *c1, *c2;
	for (int i = 0; i < entities.size(); i++) {
		c1 = entities.at(i);
		for (int j = i + 1; j < entities.size(); j++) {
			c2 = entities.at(j);

			if (matrix[c1->GetColType()][c2->GetColType()]) {
				if (CheckCollisionRecs(c1->GetRec(), c2->GetRec())) {
					c1->HasCollided(c2->GetColType());
					c2->HasCollided(c1->GetColType());
				}
			}
		}
	}
}