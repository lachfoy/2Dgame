#include "Player.h"

#include "Input.h"
#include "Renderer.h"
#include "Game.h"

Player::Player(Renderer* renderer, Texture* texture, GameState* gameState) : SpriteEntity(renderer, texture, glm::ivec2(17, 27))
{
	m_gameState = gameState;
	//m_laneIndex = 3;

	//m_desiredX = m_gameState->lanePositionsX[0];
}

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

	//if (input->IsKeyPressed(SDL_SCANCODE_A) || input->IsKeyPressed(SDL_SCANCODE_LEFT)) {
	//	if (m_laneIndex > 0)
	//	{
	//		m_laneIndex--;
	//		m_desiredX = m_gameState->lanePositionsX[m_laneIndex];
	//	}
	//}
	//if (input->IsKeyPressed(SDL_SCANCODE_D) || input->IsKeyPressed(SDL_SCANCODE_RIGHT)) {
	//	if (m_laneIndex < m_gameState->lanePositionsX.size() - 1)
	//	{
	//		m_laneIndex++;
	//		m_desiredX = m_gameState->lanePositionsX[m_laneIndex];
	//	}
	//}

}

void Player::Update(float dt)
{
	//float theta = 0.01f;
	//for (auto& vertex : m_vertexVec)
	//{
	//	glm::vec2 newPos;
	//	newPos.x = vertex.position.x * cos(theta) - vertex.position.y * sin(theta);
	//	newPos.y = vertex.position.x * sin(theta) + vertex.position.y * cos(theta);
	//	vertex.position = newPos;
	//}

	if (glm::length(m_moveDir) > 0.0f)
	{
		m_moveDir = glm::normalize(m_moveDir);
	}

	m_velocity += m_acceleration * m_moveDir * dt;
	m_velocity -= m_velocity * kFrictionCoef;

	m_position += m_velocity * dt;

	m_moveDir = glm::vec2(0.0f, 0.0f);

	//if (m_position.x != m_desiredX)
	//{
	//	// lerp
	//	m_position.x = m_position.x + (m_desiredX - m_position.x) * m_lerpRate * dt;
	//}
}
