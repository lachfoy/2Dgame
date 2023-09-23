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
	SpriteEntity(Renderer* renderer, const glm::ivec2& size = glm::ivec2(64, 64), GLuint texture = 1);
	~SpriteEntity();

	// Adds this sprites vertices to the batch
	void AddToBatch();
	
private:
	Renderer* m_renderer;
	std::vector<Vertex> m_vertices;
	unsigned int* m_indices;
	GLuint m_texture;

};