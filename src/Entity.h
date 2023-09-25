#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Entity
{
public:
	Entity();
	~Entity() {}

	void SetPosition(const glm::vec2& position);

protected:
	glm::vec2 m_position;

};