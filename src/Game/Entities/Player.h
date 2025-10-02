#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	void Init();
	void Update();
	void Draw();
	void Unload();

	void Move();

private:

	Vector2 pos;
	Texture2D sprite;
	CollisionType colType = PLAYER;

	float vel = 5;
};