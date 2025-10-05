#pragma once

#include "raylib.h"
#include "Entity.h"

class Shoot : public Entity {
public:
	Shoot();
	Shoot(Vector2 position);
	~Shoot();
	void Init();
	void Update();
	void Draw();

	void HasCollided(CollisionType type);

private:

	float vel = 10;
	int bounds;
};