#include "Projectile.h"

#include "Renderer.h"
#include "DebugRenderer.h"

Projectile::Projectile(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture)
	: SpriteEntity(renderer, debugRenderer, texture, glm::vec2(16, 16))
{
}

void Projectile::Update(float dt)
{
	m_position += m_moveDir * m_moveSpeed * dt;
}
