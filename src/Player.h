#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;
class TextureManager;

class Player : public SpriteEntity
{
public:
	Player(Renderer* renderer, DebugRenderer* debugRenderer, TextureManager* textureManager);
	~Player() {}

	void HandleInput(Input* input);
	void Update(float dt);

	void Render() override;

	void Damage(int amount);
	bool CanTakeDamage() const { return !m_immune; }

	void IncMetalCount() { m_metalCount++; }

private:
	glm::vec2 m_moveDir{ 0.0f };
	float m_acceleration = 10000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;
	float kMaxSpeed = 400.0f;

	TextureManager* m_textureManager;
	SpriteEntity m_shotgun;
	int m_metalCount = 0;

	int m_maxHealth = 100;
	int m_health = m_maxHealth;

	float m_immuneTimer = 0.0f;
	const float kImmuneInterval = 0.5f;
	bool m_immune = false;

	glm::vec2 m_aimTarget;

};