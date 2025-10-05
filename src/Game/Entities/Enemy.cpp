#pragma once

#include "raylib.h"

#include "Enemy.h"
#include "Entity.h"
#include "Game/Managers/GameManager.h"


Enemy::Enemy(Vector2 position, EnemyType type) {
	rec.x = position.x;
	rec.y = position.y;
	enemyType = type;
	Init();
}

void Enemy::Init() {
	colType = ENEMY;
	
	Image image = LoadImage(TextFormat("resources/Game/Enemy%i.png", enemyType + 1));
	sprite = LoadTextureFromImage(image);
	UnloadImage(image);

	rec.width = sprite.width;
	rec.height = sprite.height;

	if (enemyType == ENEMY_1) {
		lifes = 1;
		points = 40;
	}
	else if (enemyType == ENEMY_2) {
		lifes = 2;
		points = 50;
	}
	else if (enemyType == ENEMY_3) {
		lifes = 3;
		points = 60;
	}
}

void Enemy::Update() {
	rec.x -= vel;
	if (rec.x < 0) active = false;
}

void Enemy::Draw() {
	DrawTexture(sprite, rec.x, rec.y, WHITE);
}

void Enemy::HasCollided(CollisionType type) {
	if (type == PROJECTILE) {
		lifes--;
		if (lifes <= 0) {
			GameManager& GameInst = GameManager::GetGameManager();
			GameInst.IncreaseScore(points);
			active = false;
		}
	}
}

//------------------------------------ BOSS -------------------------------------------

Boss::Boss(Vector2 position) {
	rec.x = position.x;
	rec.y = position.y;
	Init();
}

void Boss::Init() {
	colType = ENEMY;

	// setting sprite
	Image image = LoadImage("resources/Game/Boss1.png");
	sprite = LoadTextureFromImage(image);
	UnloadImage(image);

	rec.width = sprite.width;
	rec.height = sprite.height;

	lifes = 5;
	points = 100;
}

void Boss::Update() {
	// to do
}