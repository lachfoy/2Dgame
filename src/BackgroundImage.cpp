#include "BackgroundImage.h"

#include "SpriteRenderer.h"

BackgroundImage::BackgroundImage(SpriteRenderer* renderer, Texture* texture, int width, int height)
{
	m_renderer = renderer;

	// Create the mesh data
	// This should be handled by a different class though
	Vertex vertices[] = {
		{ glm::vec2(0.0f, height), glm::vec2(0.0f, 1.0f) },
		{ glm::vec2(width, height), glm::vec2(1.0f, 1.0f) },
		{ glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2(width, 0.0f), glm::vec2(1.0f, 0.0f) }
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

void BackgroundImage::Render()
{
	RenderObject renderObject = RenderObject(
		&m_vertexVec,
		&m_indexVec,
		nullptr,
		m_texture,
		0.0f
	);

	m_renderer->AddRenderObject(renderObject);
}
