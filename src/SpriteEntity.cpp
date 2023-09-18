#include "SpriteEntity.h"

#include "Renderer.h"

SpriteEntity::SpriteEntity(Renderer* renderer, const glm::ivec2& size)
{
	m_renderer = renderer;

	// Create the mesh data
	// This should be handled by a different class though
	Vertex vertices[] = {
		{ glm::vec3(-size.x / 2.0f, size.y / 2.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec3(size.x / 2.0f, size.y / 2.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-size.x / 2.0f, -size.y / 2.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(size.x / 2.0f, -size.y / 2.0f, 0.0f), glm::vec2(1.0f, 0.0f) }
	};

	for (const auto& vertex : vertices) {
		m_vertices.push_back(vertex);
	}

	m_indices = new unsigned int[] {
		0, 1, 2,
		1, 3, 2
	};
}

SpriteEntity::~SpriteEntity()
{
	delete m_indices;
	m_vertices.clear();
}

void SpriteEntity::Render()
{
	m_renderer->AddVerticesToBatch(m_vertices, m_worldPosition);
	m_renderer->AddIndicesToBatch(m_indices, 6, m_vertices.size());
}
