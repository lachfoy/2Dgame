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

class BackgroundImage
{
public:
	BackgroundImage(Renderer* renderer, Texture* texture, int width, int height);
	~BackgroundImage() {}

	void Render();
	
protected:
	Renderer* m_renderer;
	tVertexVec m_vertexVec;
	tIndexVec m_indexVec;
	Texture* m_texture;

};