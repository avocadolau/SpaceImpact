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

	sound= GameManager::ENEMY_IMPACT;

	rec.width = sprite.width;
	rec.height = sprite.height;

	if (enemyType == ENEMY_1) {
		lives = 1;
		points = 40;
	}
	else if (enemyType == ENEMY_2) {
		lives = 2;
		points = 50;
	}
	else if (enemyType == ENEMY_3) {
		lives = 3;
		points = 60;
	}

	vel = 4;
}

void Enemy::Update() {
	rec.x -= vel;
	if (rec.x < -rec.width) active = false;
}

void Enemy::Draw() {
	DrawTexture(sprite, rec.x, rec.y, WHITE);
}

void Enemy::HasCollided(CollisionType type) {
	if (type == PROJECTILE) {
		lives--;
		if (lives <= 0) {
			GameManager& GameInst = GameManager::GetGameManager();
			GameInst.IncreaseScore(points);
			active = false;
			GameManager::GetGameManager().Play(sound);
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

	sound = GameManager::BOSS_IMPACT;

	rec.width = sprite.width;
	rec.height = sprite.height;

	lives = 5;
	points = 100;
	vel = 3;
}

void Boss::Update() {
	if (!active) shoot = false;
	if (rec.x > GetScreenWidth() / 2 + rec.width) {
		rec.x -= vel;
	}
	else {
		shoot = true;
		rec.y += vel;
		if (rec.y <= 20 || rec.y >= GetScreenHeight() - rec.height-20) vel *= -1;
	}
}