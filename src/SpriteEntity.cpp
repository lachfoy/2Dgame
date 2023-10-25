#include "SpriteEntity.h"

#include "Renderer.h"
#include "DebugRenderer.h"
#include "Texture.h"

SpriteEntity::SpriteEntity(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, glm::vec2 size)
	: m_renderer(renderer), m_debugRenderer(debugRenderer), m_texture(texture), m_size(size)
{
	// Create the mesh data
	// This should be handled by a different class though
	Vertex vertices[] = {
		{ glm::vec2(-m_size.x / 2.0f, m_size.y / 2.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec2(m_size.x / 2.0f, m_size.y / 2.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec2(-m_size.x / 2.0f, -m_size.y / 2.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2(m_size.x / 2.0f, -m_size.y / 2.0f), glm::vec2(1.0f, 0.0f) }
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
}

void SpriteEntity::RotateBy(float radians)
{
	for (auto& vertex : m_vertexVec) {
		float x = vertex.position.x;
		vertex.position.x = x * cos(radians) - vertex.position.y * sin(radians);
		vertex.position.y = x * sin(radians) + vertex.position.y * cos(radians);
	}

	m_rotation += radians;
}

void SpriteEntity::SetRotation(float radians)
{
	float diff = radians - m_rotation;

	for (auto& vertex : m_vertexVec)
	{
		float x = vertex.position.x;
		vertex.position.x = x * cos(diff) - vertex.position.y * sin(diff);
		vertex.position.y = x * sin(diff) + vertex.position.y * cos(diff);
	}

	m_rotation = radians;
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

void SpriteEntity::RenderDebugQuad()
{
	// Calculate a bounding rectangle
	glm::vec2 min{0.0f};
	glm::vec2 max{0.0f};

	for (const auto& vertex : m_vertexVec)
	{
		if (vertex.position.x < min.x) min.x = vertex.position.x;
		if (vertex.position.y < min.y) min.y = vertex.position.y;
		if (vertex.position.x > max.x) max.x = vertex.position.x;
		if (vertex.position.y > max.y) max.y = vertex.position.y;
	}

	//glm::vec2 topL = m_position - (m_size * 0.5f);
	//glm::vec2 bottomR = m_position + (m_size * 0.5f);
	//glm::vec2 bottomL = glm::vec2(topL.x, bottomR.y);
	//glm::vec2 topR = glm::vec2(bottomR.x, topL.y);

	glm::vec2 topL = min + m_position;
	glm::vec2 bottomR = max + m_position;
	glm::vec2 bottomL = glm::vec2(topL.x, bottomR.y);
	glm::vec2 topR = glm::vec2(bottomR.x, topL.y);

	const glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	m_debugRenderer->AddLine(topL, bottomL, color);
	m_debugRenderer->AddLine(bottomL, bottomR, color);
	m_debugRenderer->AddLine(bottomR, topR, color);
	m_debugRenderer->AddLine(topR, topL, color);
}
