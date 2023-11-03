#include "Enemy.h"

#include "Input.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"

Enemy::Enemy(Renderer* renderer, DebugRenderer* debugRenderer, glm::vec2 position, Texture* texture, TextureManager* textureManager)
	: SpriteEntity(renderer, debugRenderer, texture, position, glm::vec2(16, 16)), m_textureManager(textureManager)
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

void Enemy::Think(const Player& player)
{
	// set direction to move towards player
	m_moveDir = glm::normalize(player.GetPosition() - m_position);
}

void Enemy::Update(float dt, const Player& player)
{
	m_thinkTimer += dt;
	if (m_thinkTimer >= kThinkInterval)
	{
		m_thinkTimer = 0.0f;
		Think(player);
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
	//metal.push_back(std::make_unique<Metal>(m_renderer, m_debugRenderer, m_position, m_textureManager->GetTexture("diamond"), m_player));
}
