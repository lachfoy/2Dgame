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
	SpriteEntity(Renderer* renderer, Texture* texture);
	~SpriteEntity() {}

	glm::vec2 GetSize() const { return m_size; }
	glm::vec2 GetExtents() const { return m_size * 0.5f; }

	void Render();
	void RenderDebugQuad();
	
protected:
	Renderer* m_renderer;
	tVertexVec m_vertexVec;
	tIndexVec m_indexVec;
	Texture* m_texture;
	glm::vec2 m_size;

};

static bool Collision(const SpriteEntity& objA, const SpriteEntity& objB)
{
	const glm::vec2& aCenter = objA.GetPosition();
	const glm::vec2& bCenter = objB.GetPosition();
	const glm::vec2& aExtents = objA.GetExtents();
	const glm::vec2& bExtents = objB.GetExtents();
	
	float xDiff = abs(aCenter.x - bCenter.x);
	float yDiff = abs(aCenter.y - bCenter.y);

	return (
		xDiff <= aExtents.x + bExtents.x &&
		yDiff <= aExtents.y + bExtents.y
	);
}