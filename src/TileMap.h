#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

#include "Vertex.h"
#include "Texture.h"

class Renderer;

typedef std::vector<Vertex> tVertexVec;
typedef std::vector<unsigned int> tIndexVec;

class TileMap
{
public:
	TileMap(Renderer* renderer, Texture* texture) : m_renderer(renderer), m_texture(texture) {}
	~TileMap() = default;
	
	void CreateDebugMap();
	void BuildTileMesh();

	void Render();
	void Destroy();

private:
	Renderer* m_renderer;
	tVertexVec m_vertexVec;
	tIndexVec m_indexVec;
	Texture* m_texture;

	int* m_tileData;
	int m_width;
	int m_height;

};