#pragma once

#include "raylib.h"
#include "Entity.h"

class Shoot : public Entity {
public:
	enum ShootDirection {
		R,
		L
	};

	Shoot();
	Shoot(Vector2 position, ShootDirection direction);
	~Shoot();
	void Init();
	void Update();
	void Draw();

	void HasCollided(CollisionType type);

private:

	float vel = 10;
	int bounds;
};