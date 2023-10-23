#include "Enemy.h"

#include "Input.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "Player.h"
#include "TextureManager.h"

Enemy::Enemy(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, std::vector<std::unique_ptr<Metal>>* metal, TextureManager* textureManager)
	: SpriteEntity(renderer, debugRenderer, texture), m_player(player), m_metal(metal), m_textureManager(textureManager)
{
}

void Enemy::Think()
{
	// set direction to move towards player
	glm::vec2 targetPosition = m_player->GetPosition();
	m_moveDir = glm::normalize(targetPosition - m_position);

	// this is not good but whatever
	//std::unique_ptr<Metal> metal = std::make_unique<Metal>(m_renderer, m_debugRenderer, m_textureManager->GetTexture("metal"), m_player);
	//metal->SetPosition(m_position);
	//m_metal->push_back(std::move(metal));
}

void Enemy::Update(float dt)
{
	m_thinkTimer += dt;
	if (m_thinkTimer >= kThinkInterval)
	{
		m_thinkTimer = 0.0f;
		Think();
	}

	if (glm::length(m_moveDir) > 0.0f)
	{
		m_moveDir = glm::normalize(m_moveDir);
	}

	m_velocity += m_acceleration * m_moveDir * dt;
	m_velocity -= m_velocity * kFrictionCoef;

	m_position += m_velocity * dt;
}
