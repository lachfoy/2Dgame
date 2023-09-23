#pragma once

#include "Entity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

#include "Vertex.h"
#include "Texture.h"

class Renderer;

typedef std::vector<Vertex> tVertexVec;
typedef std::vector<unsigned int> tIndexVec;

class SpriteEntity : public Entity
{
public:
	SpriteEntity(Renderer* renderer, const glm::ivec2& size = glm::ivec2(64, 64), GLuint texture = 1);
	~SpriteEntity();

	// Adds this sprites m_vertexVec to the batch
	void AddToBatch();
	
private:
	Renderer* m_renderer;
	tVertexVec m_vertexVec;
	tIndexVec m_indexVec;
	GLuint m_texture;

};