#pragma once

#include "Entity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

#include "Vertex.h"

class Renderer;

class SpriteEntity : public Entity
{
public:
	SpriteEntity(Renderer* renderer, const glm::vec2& size = glm::vec2(64.0f, 64.0f));
	~SpriteEntity();

	// Adds this sprites vertices to the batch
	void Render();
	
private:
	Renderer* m_renderer;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

};