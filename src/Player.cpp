#include "Player.h"

#include "Input.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"

Player::Player(Renderer* renderer, DebugRenderer* debugRenderer, glm::vec2 position, TextureManager* textureManager, std::vector<std::unique_ptr<Projectile>>* projectiles)
	: SpriteEntity(renderer, debugRenderer, nullptr, position, glm::vec2(16, 16)), m_textureManager(textureManager), m_projectiles(projectiles)
{
	m_texture = m_textureManager->GetTexture("guy");
	m_shotgun = SpriteEntity(renderer, debugRenderer, m_textureManager->GetTexture("shotgun"), m_position, glm::vec2(16, 8));
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

	m_aimTarget = input->GetMouseAbsPos() / 2.0f;

	if (input->IsMouseButtonDown(SDL_BUTTON_LEFT))
	{
		glm::vec2 aimDirection = glm::normalize(m_aimTarget - m_position);
		m_projectiles->push_back(std::make_unique<Projectile>(m_renderer, m_debugRenderer, m_position, m_textureManager->GetTexture("bullet"), aimDirection));
	}
}

void Player::Update(float dt)
{
	if (m_immune) // replace this with a timer class probably
	{
		m_immuneTimer += dt;
		if (m_immuneTimer >= kImmuneInterval)
		{
			m_immuneTimer = 0.0f;
			m_immune = false;
		}
	}

	if (glm::length(m_moveDir) > 0.0f)
	{
		m_moveDir = glm::normalize(m_moveDir);
	}

	// Rotate the shotgun towards the mouse
	glm::vec2 aimDirection = glm::normalize(m_aimTarget - m_position);
	float aimAngle = atan2(aimDirection.y, aimDirection.x);
	m_shotgun.SetRotation(aimAngle);

	// Apply movement
	m_velocity += m_acceleration * m_moveDir * dt;
	m_velocity -= m_velocity * kFrictionCoef;

	m_position += m_velocity * dt;
	m_shotgun.SetPosition(m_position);

	// Flip the shotgun sprite if necessary
	if (m_position.x > m_aimTarget.x)
	{
		m_shotgun.SetFlipPolicy(FlipPolicy::FlipX);
	}
	else
	{
		m_shotgun.SetFlipPolicy(FlipPolicy::DoNotFlip);
	}

	m_moveDir = glm::vec2(0.0f, 0.0f);
}

void Player::Damage(int amount)
{
	if (m_health > 0)
	{
		m_health -= amount;
		printf("Player took %d damage! New hp = %d/%d\n", amount, m_health, m_maxHealth);

		if (m_health <= 0)
		{
			printf("Dead!!!!!\n");
		}
		else
		{
			// kick immunity timer
			m_immune = true;
		}
	}
}

void Player::Render()
{
	SpriteEntity::Render();
	m_shotgun.Render();
}

