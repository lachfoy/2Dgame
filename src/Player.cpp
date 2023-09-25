#include "Player.h"

#include "Input.h"

void Player::HandleInput(Input* input)
{
	if (input->IsKeyHeld(SDL_SCANCODE_W) || input->IsKeyHeld(SDL_SCANCODE_UP)) {
		m_moveDir.y = -1.0f;
	}
	if (input->IsKeyHeld(SDL_SCANCODE_A) || input->IsKeyHeld(SDL_SCANCODE_LEFT)) {
		m_moveDir.x = -1.0f;
	}
	if (input->IsKeyHeld(SDL_SCANCODE_S) || input->IsKeyHeld(SDL_SCANCODE_DOWN)) {
		m_moveDir.y = 1.0f;
	}
	if (input->IsKeyHeld(SDL_SCANCODE_D) || input->IsKeyHeld(SDL_SCANCODE_RIGHT)) {
		m_moveDir.x = 1.0f;
	}
}

void Player::Update(float dt)
{
	float theta = 0.01f;
	for (auto& vertex : m_vertexVec)
	{
		glm::vec2 newPos;
		newPos.x = vertex.position.x * cos(theta) - vertex.position.y * sin(theta);
		newPos.y = vertex.position.x * sin(theta) + vertex.position.y * cos(theta);
		vertex.position = newPos;
	}

	if (glm::length(m_moveDir) > 0.0f)
	{
		m_moveDir = glm::normalize(m_moveDir);
	}

	m_velocity += m_acceleration * m_moveDir * dt;
	m_velocity -= m_velocity * kFrictionCoef;

	m_position += m_velocity * dt;

	m_moveDir = glm::vec2(0.0f, 0.0f);
}
