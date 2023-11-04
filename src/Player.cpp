#include "Player.h"

#include "Input.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "TextureManager.h"

Player::Player(glm::vec2 position, std::vector<std::unique_ptr<Projectile>>* projectiles)
	: SpriteEntity(position, glm::vec2(16, 16), gTextureManager.GetTexture("guy")), m_projectiles(projectiles)
{
	m_shotgun = SpriteEntity(m_position, glm::vec2(16, 8), gTextureManager.GetTexture("shotgun"));
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

	if (input->IsMouseButtonPressed(SDL_BUTTON_LEFT))
	{
		Shoot();
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

void Player::Shoot()
{
	glm::vec2 aimDirection = glm::normalize(m_aimTarget - m_position);
	float aimAngle = atan2(aimDirection.y, aimDirection.x);

	float shotSpreadRadians = m_shotSpread * (M_PI / 180.0);

	for (int i = 0; i < m_numShots; i++)
	{
		float angle = aimAngle - shotSpreadRadians / 2.0 + ((float)rand() / RAND_MAX) * shotSpreadRadians;

		glm::vec2 shotDirection = glm::vec2(cos(angle), sin(angle));
		m_projectiles->push_back(std::make_unique<Projectile>(m_position, shotDirection));
	}
}

void Player::Render(Renderer* renderer)
{
	SpriteEntity::Render(renderer);
	m_shotgun.Render(renderer);
}

