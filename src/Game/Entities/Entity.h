#pragma once
#include "raylib.h"


enum CollisionType {
	PLAYER,
	PROJECTILE,
	ENEMY
};

class Entity
{
public:
	void Init();
	void Update();
	void Draw();
	void Unload();

	void Move();
private:
	Vector2 pos;
	float vel;
	Texture2D sprite;
	CollisionType colType;
};