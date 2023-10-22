#include "Turret.h"

#include "Input.h"
#include "Renderer.h"
#include "Game.h"

Turret::Turret(Renderer* renderer, Texture* texture, std::vector<std::unique_ptr<Enemy>>* enemies) : SpriteEntity(renderer, texture), m_enemies(enemies)
{
}

void Turret::Think()
{
	int i = rand() % m_enemies->size();
	std::unique_ptr<Enemy>& enemy = m_enemies->at(i);

	m_renderer->AddDebugLine(m_position, enemy->GetPosition()); // make this line have a timer
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
