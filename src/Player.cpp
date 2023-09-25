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
	if (glm::length(m_moveDir) > 0.0f)
	{
		m_moveDir = glm::normalize(m_moveDir);
	}

	m_position.x += m_moveDir.x * m_moveSpeed * dt;
	m_position.y += m_moveDir.y * m_moveSpeed * dt;
	m_moveDir = glm::vec2(0.0f, 0.0f);
}
