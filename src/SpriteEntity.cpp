#include "SpriteEntity.h"

#include "Renderer.h"

SpriteEntity::SpriteEntity(Renderer* renderer, Texture* texture, const glm::ivec2& size)
{
	m_renderer = renderer;

	// Create the mesh data
	// This should be handled by a different class though
	Vertex vertices[] = {
		{ glm::vec2(-size.x / 2.0f, size.y / 2.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec2(size.x / 2.0f, size.y / 2.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec2(-size.x / 2.0f, -size.y / 2.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2(size.x / 2.0f, -size.y / 2.0f), glm::vec2(1.0f, 0.0f) }
	};

	for (const auto& vertex : vertices) {
		m_vertexVec.push_back(vertex);
	}

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2
	};

	for (const auto& index : indices) {
		m_indexVec.push_back(index);
	}

	m_texture = texture;
}

void SpriteEntity::Render()
{
	RenderObject renderObject = RenderObject(
		&m_vertexVec,
		&m_indexVec,
		&m_position,
		m_texture
	);

	m_renderer->AddRenderObject(renderObject);
}
