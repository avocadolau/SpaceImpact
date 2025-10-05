#pragma once

#include "raylib.h"

#include "Shoot.h"
#include "Entity.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"


Shoot::Shoot() {

}

Shoot::Shoot(Vector2 position) {
	rec.x = position.x;
	rec.y = position.y;
	Init();
}

Shoot::~Shoot() {
}

void Shoot::Init() {
	rec.width = 40;
	rec.height = 10;
	colType = PROJECTILE;
}

void Shoot::Update() {
	rec.x += vel;
	if (rec.x > GetScreenWidth()) active = false;
}

void Shoot::Draw() {
	DrawRectangle(rec.x, rec.y, rec.width, rec.height, LIGHTGREEN);
}

void Shoot::HasCollided(CollisionType type) {
	active = false;
}