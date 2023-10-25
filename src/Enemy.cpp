#include "Enemy.h"

#include "Input.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "Player.h"
#include "TextureManager.h"

Enemy::Enemy(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, TextureManager* textureManager)
	: SpriteEntity(renderer, debugRenderer, texture), m_player(player), m_textureManager(textureManager)
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

void Enemy::OnDestroy(std::vector<std::unique_ptr<Metal>>& metal)
{
	std::unique_ptr<Metal> m = std::make_unique<Metal>(m_renderer, m_debugRenderer, m_textureManager->GetTexture("metal"), m_player);
	m->SetPosition(m_position);
	metal.push_back(std::move(m));
}
