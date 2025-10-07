#pragma once

#include "Entity.h"
#include "Game/Managers/GameManager.h"

class Enemy : public Entity {
public:
	enum EnemyType {
		ENEMY_1,
		ENEMY_2,
		ENEMY_3
	};

	Enemy() {}
	Enemy(Vector2 position,EnemyType type);
	~Enemy() {}
	virtual void Init();
	virtual void Update();
	void Draw();
	void HasCollided(CollisionType type);

protected:
	Texture2D sprite;
	EnemyType enemyType;
	GameManager::Sounds sound;

	int lives;
	int points;
};

class Boss : public Enemy {
public:
	Boss(Vector2 position);
	~Boss() {}

	void Init();
	void Update();
public:
	bool shoot = false;
};