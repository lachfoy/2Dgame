#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Player : public SpriteEntity
{
public:
	Player(Renderer* renderer) : SpriteEntity(renderer) {}
	~Player() {}

	void HandleInput();

private:

};