#include "Enemy.h"

#include "Input.h"
#include "SpriteRenderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"
#include "Player.h"

Enemy::Enemy(glm::vec2 position, Player* player, std::vector<Turret*>& turrets)
	: SpriteEntity(position, glm::vec2(16, 16), gTextureManager.GetTexture("enemy")), m_player(player), m_turrets(turrets)
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
	// todo just redo this... 
	if (m_hasTarget) return;
	
	int targetIndex = rand() % m_turrets.size() + 1;

	// select random turret or player
	m_targetPos = (targetIndex == m_turrets.size()) ? m_player->GetPosition() : m_turrets[targetIndex]->GetPosition();

	m_hasTarget = true;
}

void Enemy::Update(float dt)
{
	m_thinkTimer += dt;
	if (m_thinkTimer >= kThinkInterval)
	{
		m_thinkTimer = 0.0f;
		Think();
	}

	// set direction to move towards target
	m_moveDir = glm::normalize(m_targetPos - m_position);

	// Apply movement
	m_velocity -= m_velocity * kFrictionCoef * dt;
	m_velocity += m_acceleration * m_moveDir * dt;

	m_position += m_velocity * dt;
}

void Enemy::OnRemove(std::vector<std::unique_ptr<Metal>>& metal)
{
	metal.push_back(std::make_unique<Metal>(m_position, m_player));
}
