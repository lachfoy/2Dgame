#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Metal.h"

class Input;
class Player;
class TextureManager;

class Enemy : public SpriteEntity
{
public:
	Enemy(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, std::vector<std::unique_ptr<Metal>>* metal, TextureManager* textureManager);
	~Enemy() {}

	bool GetRemove() const { return m_remove; }

	void Think();
	void Update(float dt);

private:
	glm::vec2 m_moveDir{ 0.0f };
	
	float m_acceleration = 1000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;

	Player* m_player;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 3.5f;

	std::vector<std::unique_ptr<Metal>>* m_metal;
	TextureManager* m_textureManager;

	int m_maxHealth = 10;
	int m_health = m_maxHealth;

	bool m_remove = false;

};