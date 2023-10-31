#include "Projectile.h"

#include "Renderer.h"
#include "DebugRenderer.h"

Projectile::Projectile(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, glm::vec2 direction)
	: SpriteEntity(renderer, debugRenderer, texture, glm::vec2(4, 4)), m_moveDir(direction)
{
}

void Projectile::Update(float dt)
{
	m_position += m_moveDir * m_moveSpeed * dt;
}
