#include "Enemy.h"

#include "Input.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"
#include "Player.h"

Enemy::Enemy(Renderer* renderer, DebugRenderer* debugRenderer, TextureManager* textureManager, glm::vec2 position, Player* player)
	: SpriteEntity(renderer, debugRenderer, textureManager, textureManager->GetTexture("enemy"), position, glm::vec2(16, 16)), m_player(player)
{
}

void Enemy::Damage(int amount)
{
	m_health -= amount;
	printf("enemy damaged for %d. New hp = %d/%d\n", amount, m_health, m_maxHealth);

	if (m_health <= 0)
	{
		m_remove = true;
		printf("Enemy destroyed\n");
	}
}

void Enemy::Think()
{
	// set direction to move towards player
	m_moveDir = glm::normalize(m_player->GetPosition() - m_position);
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

void Enemy::OnRemove(std::vector<std::unique_ptr<Metal>>& metal)
{
	metal.push_back(std::make_unique<Metal>(m_renderer, m_debugRenderer, m_textureManager, m_position, m_player));
}
