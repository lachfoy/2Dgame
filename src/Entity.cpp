#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity()
{
    m_worldPosition = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Entity::SetWorldPosition(const glm::vec3& worldPosition)
{
	m_worldPosition = worldPosition;
}
