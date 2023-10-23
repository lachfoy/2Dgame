#include "Turret.h"

#include "Renderer.h"
#include "DebugRenderer.h"

Turret::Turret(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, std::vector<std::unique_ptr<Enemy>>* enemies)
	: SpriteEntity(renderer, debugRenderer, texture), m_enemies(enemies)
{
}

void Turret::Think()
{
	if (!m_enemies->empty())
	{
		int i = rand() % m_enemies->size();
		std::unique_ptr<Enemy>& enemy = m_enemies->at(i);

		m_debugRenderer->AddLine(m_position, enemy->GetPosition(), glm::vec3(0.0f, 1.0f, 0.0f), 0.5f);
	}
}

void Turret::Update(float dt)
{
	m_thinkTimer += dt;
	if (m_thinkTimer >= kThinkInterval)
	{
		m_thinkTimer = 0.0f;
		Think();
	}

}
