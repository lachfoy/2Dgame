#include "Metal.h"

#include "Renderer.h"
#include "DebugRenderer.h"
#include "Player.h"

Metal::Metal(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player)
	: SpriteEntity(renderer, debugRenderer, texture), m_player(player)
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

	printf("ACTIVE!!!\n");
}
