#pragma once

#include "raylib.h"

#include "Entity.h"

Entity::Entity() {
	Init();
}

Entity::Entity(Vector2 position) {
	rec.x = position.x;
	rec.y = position.y;

	Init();
}