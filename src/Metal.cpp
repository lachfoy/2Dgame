#include "Metal.h"

#include "Renderer.h"
#include "DebugRenderer.h"
#include "Player.h"

Metal::Metal(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player)
	: SpriteEntity(renderer, debugRenderer, texture, glm::vec2(8, 8)), m_player(player)
{
}

void Metal::Think()
{
	float distance = glm::length(m_player->GetPosition() - m_position);
	if (distance <= m_activationRadius)
	{
		m_active = true;
	}
}

void Metal::Update(float dt)
{
	m_thinkTimer += dt;
	if (m_thinkTimer >= kThinkInterval)
	{
		m_thinkTimer = 0.0f;
		Think();
	}

	if (!m_active) return;

	glm::vec2 moveDir = glm::normalize(m_player->GetPosition() - m_position);

	m_velocity += m_acceleration * moveDir * dt;
	m_velocity -= m_velocity * kFrictionCoef;

	m_position += m_velocity * dt;
}
