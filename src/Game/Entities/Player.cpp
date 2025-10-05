#pragma once

#include "raylib.h"

#include "Player.h"
#include "Game/Managers/GameManager.h"

Player::Player() {

	Init();
}

Player::Player(Vector2 position, Rectangle limits) {
	
	rec.x = position.x;
	rec.y = position.y;
	bounds = limits;
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
		if (rec.x < bounds.x) rec.x = bounds.x;
	}

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		rec.x += vel;
		if (rec.x > bounds.x + bounds.width - rec.width) rec.x = bounds.x + bounds.width - rec.width;
	}

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
		rec.y -= vel;
		if (rec.y < bounds.y) rec.y = bounds.y;
	}

	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
		rec.y += vel;
		if (rec.y > bounds.y + bounds.height- rec.height) rec.y = bounds.y + bounds.height-rec.height;
	}

	
}

void Player::Draw() {

	DrawTexture(sprite, rec.x, rec.y, WHITE);
	//DrawRectangle(rec.x, rec.y, rec.width, rec.height, RED);
}

void Player::HasCollided(CollisionType type) {
	GameManager& GameInst = GameManager::GetGameManager();
	GameInst.DecreaseLifes();
}

