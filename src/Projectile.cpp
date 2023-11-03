#include "Projectile.h"

#include "Renderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"

Projectile::Projectile(Renderer* renderer, DebugRenderer* debugRenderer, TextureManager* textureManager, glm::vec2 position, glm::vec2 direction)
	: SpriteEntity(renderer, debugRenderer, textureManager, textureManager->GetTexture("bullet"), position, glm::vec2(4, 4)), m_moveDir(direction)
{
	m_rotation = atan2(m_moveDir.y, m_moveDir.x);
}

void Projectile::Update(float dt)
{
	m_lifeTime -= dt;
	if (m_lifeTime <= 0.0f)
	{
		m_remove = true;
		return;
	}

	m_position += m_moveDir * m_moveSpeed * dt;
}
