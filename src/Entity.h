#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Entity
{
public:
	Entity();
	~Entity() {}

	void SetWorldPosition(const glm::vec2& worldPosition);

protected:
	glm::vec2 m_worldPosition;

};