#include "World.h"

#include "Projectile.h"

World::World(SpriteRenderer* spriteRenderer, TextureManager* textureManager)
	: m_spriteRenderer(spriteRenderer), m_textureManager(textureManager)
{
}

World::~World()
{
	for (const auto& projectile : m_projectiles)
	{
		delete projectile;
	}
}

void World::Update(float dt)
{
	for (const auto& projectile : m_projectiles)
	{
		projectile->Update(dt);
	}

}

void World::Render()
{
	for (const auto& projectile : m_projectiles)
	{
		projectile->Render(m_spriteRenderer);
	}
}

Projectile* World::AddProjectile(glm::vec2 position, glm::vec2 direction, ProjectileType type)
{
	Projectile* projectile = new Projectile(position, direction, type);
	m_projectiles.push_back(projectile);

	return projectile;
}

void World::CleanUpDeleteList()
{

}
