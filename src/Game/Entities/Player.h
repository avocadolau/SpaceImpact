#pragma once

#include "Entity.h"


class Player : public Entity {
public:
	Player();
	Player(Vector2 position);
	~Player();
	void Init();
	void Update();
	void Draw();
	void HasCollided(CollisionType type);

private:
	Texture2D sprite;
	int damageCooldown = 0;
	float vel = 5;
};