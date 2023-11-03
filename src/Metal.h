#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;
class Player;

class Metal : public SpriteEntity
{
public:
	Metal(Renderer* renderer, DebugRenderer* debugRenderer, TextureManager* textureManager, glm::vec2 position, Player* player);
	~Metal() {}

	void Think(); // exact same as enemy
	void Update(float dt);

private:
	Player* m_player;

	glm::vec2 m_moveDir{ 0.0f };

	float m_acceleration = 10000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 0.5f;

	bool m_active = false;
	float m_activationRadius = 60.0f;

};