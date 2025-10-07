#pragma once

#include "raylib.h"

#include "Player.h"
#include "Game/Managers/GameManager.h"

Player::Player() {

	Init();
}

Player::Player(Vector2 position) {
	
	rec.x = position.x;
	rec.y = position.y;
	Init();
}

Player::~Player() {

}

void Player::Init() {
	colType = PLAYER;

	// setting sprite
	Image image = LoadImage("resources/Game/Player.png");
	sprite = LoadTextureFromImage(image);
	UnloadImage(image);

	rec.width = sprite.width;
	rec.height = sprite.height;
}

void Player::Update() {
	// input

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		rec.x -= vel;
		if (rec.x < 0) rec.x = 0;
	}

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		rec.x += vel;
		if (rec.x > GetScreenWidth() - rec.width) rec.x = GetScreenWidth() - rec.width;
	}

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
		rec.y -= vel;
		if (rec.y < 90) rec.y = 90;
	}

	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
		rec.y += vel;
		if (rec.y > GetScreenHeight() - rec.height) rec.y = GetScreenHeight() - rec.height;
	}

	if (damageCooldown > 0) damageCooldown-=(float)1/GetFPS();
	
}

void Player::Draw() {
	
	if (damageCooldown > 0) {		// dmg visual feedback
		if (damageCooldown % 10 > 4) DrawTexture(sprite, rec.x, rec.y, Fade(WHITE, 0.3f));
		else DrawTexture(sprite, rec.x, rec.y, WHITE);
	}
	else DrawTexture(sprite, rec.x, rec.y, WHITE);
}

void Player::HasCollided(CollisionType type) {
	if (damageCooldown <= 0) {
		GameManager& GameInst = GameManager::GetGameManager();
		GameInst.DecreaseLifes();
		GameInst.Play(GameManager::PLAYER_IMPACT);
		damageCooldown = 50;
	}
}

