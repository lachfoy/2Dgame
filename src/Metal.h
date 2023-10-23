#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;
class Player;

class Metal : public SpriteEntity
{
public:
	Metal(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player);
	~Metal() {}

	void Think(); // exact same as enemy
	void Update(float dt);

private:
	Player* m_player;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 0.5f;

	bool m_active = false;
	float m_activationRadius = 30.0f;

};