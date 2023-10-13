#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec2 position;
	glm::vec2 texCoord;

	inline static Vertex Make(glm::vec2 positon, glm::vec2 texCoord)
	{
		Vertex vertex;
		vertex.position = positon;
		vertex.texCoord = texCoord;
		return vertex;
	}
};
