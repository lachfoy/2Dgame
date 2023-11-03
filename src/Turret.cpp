#include "Turret.h"

#include "Renderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"

Turret::Turret(Renderer* renderer, DebugRenderer* debugRenderer, TextureManager* textureManager, glm::vec2 position, std::vector<std::unique_ptr<Enemy>>* enemies)
	: SpriteEntity(renderer, debugRenderer, textureManager, textureManager->GetTexture("turret"), position, glm::vec2(16, 16)), m_enemies(enemies)
{
	//debugRenderer->AddCircle(position, m_detectRadius, glm::vec3(0.0f, 1.0f, 1.0f)); //whar
}

void Turret::Think()
{
	if (!m_enemies->empty())
	{
		// Find enemies within range
		std::vector<int> enemiesInRangeIndices;
		for (int i = 0; i < m_enemies->size(); i++)
		{
			std::unique_ptr<Enemy>& enemy = m_enemies->at(i);

			float dist = glm::length(enemy->GetPosition() - m_position);
			if (dist < m_detectRadius)
			{
				enemiesInRangeIndices.push_back(i);
			}
		}

		// If enemies are in range, pick one at random as a target
		if (!enemiesInRangeIndices.empty())
		{
			int i = rand() % enemiesInRangeIndices.size();
			std::unique_ptr<Enemy>& enemy = m_enemies->at(enemiesInRangeIndices.at(i));

			glm::vec2 directionToEnemy = glm::normalize(enemy->GetPosition() - m_position);
			float angleToEnemy = atan2(directionToEnemy.y, directionToEnemy.x);
			SetRotation(angleToEnemy);

			m_debugRenderer->AddLine(m_position, enemy->GetPosition(), glm::vec3(0.0f, 1.0f, 0.0f), 0.5f);
			enemy->Damage(rand() % 5);
		}
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
