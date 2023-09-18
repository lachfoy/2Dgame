#include "SpriteEntity.h"

#include "Renderer.h"

SpriteEntity::SpriteEntity(Renderer* renderer, const glm::vec2& size)
{
	m_renderer = renderer;

	// hardcode coords
	float spriteSize = 1.0f / 6.0f;
	float rowCoord = rand() % 3 * (1.0f / 6.0f);
	float colCoord = rand() % 6 * (1.0f / 6.0f);

	// Create the mesh data
	// This should be handled by a different class though. OR something
	Vertex vertices[] = {
		{ glm::vec3(-size.x / 2.0f, size.y / 2.0f, 0.0f), glm::vec2(colCoord, rowCoord + spriteSize) },
		{ glm::vec3(size.x / 2.0f, size.y / 2.0f, 0.0f), glm::vec2(colCoord + spriteSize, rowCoord + spriteSize) },
		{ glm::vec3(-size.x / 2.0f, -size.y / 2.0f, 0.0f), glm::vec2(colCoord, rowCoord) },
		{ glm::vec3(size.x / 2.0f, -size.y / 2.0f, 0.0f), glm::vec2(colCoord + spriteSize, rowCoord) }
	};

	for (const auto& vertex : vertices) {
		m_vertices.push_back(vertex);
	}

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2
	};

	for (const auto& index : indices) {
		m_indices.push_back(index);
	}
}

SpriteEntity::~SpriteEntity()
{
	m_vertices.clear();
	m_indices.clear();
}

void SpriteEntity::Render()
{
	m_renderer->AddVerticesToBatch(m_vertices, m_worldPosition);
	m_renderer->AddIndicesToBatch(m_indices);
}
