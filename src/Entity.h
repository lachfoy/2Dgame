#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Entity
{
public:
	Entity();
	~Entity() {}

	void SetWorldPosition(const glm::vec3& worldPosition);

protected:
	glm::vec3 m_worldPosition;

};