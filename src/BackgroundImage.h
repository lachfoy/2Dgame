#pragma once

#include "Entity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

#include "Vertex.h"
#include "Texture.h"

class SpriteRenderer;

typedef std::vector<Vertex> tVertexVec;
typedef std::vector<unsigned int> tIndexVec;

class BackgroundImage
{
public:
	BackgroundImage(SpriteRenderer* renderer, Texture* texture, int width, int height);
	~BackgroundImage() {}

	void Render();
	
protected:
	SpriteRenderer* m_renderer;
	tVertexVec m_vertexVec;
	tIndexVec m_indexVec;
	Texture* m_texture;

};