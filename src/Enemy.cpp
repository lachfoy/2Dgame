#include "Enemy.h"

#include "Input.h"
#include "Renderer.h"
#include "Player.h"

Enemy::Enemy(Renderer* renderer, Texture* texture, Player* player) : SpriteEntity(renderer, texture, glm::ivec2(36, 52)), m_player(player)
{

}

void Enemy::Update(float dt)
{
	//float theta = 0.01f;
	//for (auto& vertex : m_vertexVec)
	//{
	//	glm::vec2 newPos;
	//	newPos.x = vertex.position.x * cos(theta) - vertex.position.y * sin(theta);
	//	newPos.y = vertex.position.x * sin(theta) + vertex.position.y * cos(theta);
	//	vertex.position = newPos;
	//}

	//if (glm::length(m_moveDir) > 0.0f)
	//{
	//	m_moveDir = glm::normalize(m_moveDir);
	//}

	//m_velocity += m_acceleration * m_moveDir * dt;
	//m_velocity -= m_velocity * kFrictionCoef;

	//m_position += m_velocity * dt;

	//m_moveDir = glm::vec2(0.0f, 0.0f);

	m_position.x -= m_moveSpeed * dt;
}
