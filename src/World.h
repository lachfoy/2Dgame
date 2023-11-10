#pragma once

//#include <iterator>
#include <list>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class TextureManager;
class SpriteRenderer;

class SpriteEntity;

class Projectile;
enum class ProjectileType;

class World
{
public:
	World(SpriteRenderer* spriteRenderer, TextureManager* textureManager);
	~World();

	void Update(float dt);
	void Render();

	//SpriteEntity* AddSpriteEntity(std::string name, std::string dataPath);

	Projectile* AddProjectile(glm::vec2 position, glm::vec2 direction, ProjectileType type);

	void CleanUpDeleteList();

private:

	SpriteRenderer* m_spriteRenderer; // non owning
	TextureManager* m_textureManager; // non owning

	//std::list<SpriteEntity*> m_spriteEntities;

	std::list<Projectile*> m_projectiles;


};
