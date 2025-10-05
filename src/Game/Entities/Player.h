#pragma once

#include "Entity.h"


class Player : public Entity {
public:
	Player();
	Player(Vector2 position, Rectangle limits);
	~Player();
	void Init();
	void Update();
	void Draw();
	void HasCollided(CollisionType type);

private:
	Rectangle bounds;
	Texture2D sprite;

	float vel = 5;
};