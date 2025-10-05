
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

	Image landscapeImg = LoadImage("resources/Game/Landscape.png");
	landscape = LoadTextureFromImage(landscapeImg);
	UnloadImage(landscapeImg);
	bounds.x = (GetScreenWidth() / 2 - landscape.width / 2);
	bounds.y = GetScreenHeight() / 2 - landscape.height / 2;
	bounds.width = landscape.width;
	bounds.height = landscape.height;

	Vector2 playerPos;
	playerPos.x = (GetScreenWidth() / 2 - landscape.width / 2) + 10;
	playerPos.y = GetScreenHeight() / 2;

	// Init Player & entities list
	player = new Player(playerPos,bounds);
	entities.push_back(player);

	// seting collisions
	matrix[PLAYER][PLAYER] = false;
	matrix[PLAYER][PROJECTILE] = false;
	matrix[PLAYER][ENEMY] = true;

	matrix[PROJECTILE][PLAYER] = false;
	matrix[PROJECTILE][PROJECTILE] = false;
	matrix[PROJECTILE][ENEMY] = true;

	matrix[ENEMY][PLAYER] = true;
	matrix[ENEMY][PROJECTILE] = true;
	matrix[ENEMY][ENEMY] = false;
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();

	framesCounter++;
	// tengo q meter spawneo enemigos


	if (shootCooldown > 0) shootCooldown--;

	// Controlls

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 2;   // GAMEPLAY
	}

	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // OPTIONS
	}

	if (IsKeyDown(KEY_SPACE) && shootCooldown == 0) {
		// PIUM PIUM
		Vector2 newPos;
		newPos.x = player->GetRec().x + player->GetRec().width;
		newPos.y = player->GetRec().y + player->GetRec().height / 2;
		Shoot* nShoot = new Shoot(newPos);
		entities.push_back(nShoot);

		shootCooldown = 20;
	}

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
	Font font = GameInst.GetFont();
	DrawText("SCORE:", 300.f, 100.f, 25, LIGHTGREEN);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, LIGHTGREEN);
}

void ScreenGameplayState::UnloadScreen(void)
{
	// delete pllayer and all entities
	delete player;
	/*for (int i = 0; i < entities.size(); i++) {
		Entity* e = entities.at(i);
		delete e;
		entities.at(i) = nullptr;
	}*/
	entities.clear();
}

int  ScreenGameplayState::FinishScreen(void)
{
	// check entities to delete
	bool finish = false;
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