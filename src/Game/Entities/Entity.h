#pragma once
#include "raylib.h"

enum CollisionType {
	PLAYER,
	PROJECTILE,
	ENEMY,
	MAX
};

class Entity
{
public:
	Entity();
	Entity(Vector2 position);
	~Entity(){}

	virtual void Init(){}
	virtual void Update(){}
	virtual void Draw(){}
	virtual void HasCollided(CollisionType type) {}

	virtual bool IsActive() { return active; }
	virtual Rectangle GetRec() { return rec; }
	virtual CollisionType GetColType() { return colType; }

protected:
	Rectangle rec;
	CollisionType colType;
	
	float vel;
	bool active = true;
};