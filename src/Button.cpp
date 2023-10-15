#include "Button.h"

#include "Input.h"

Button::Button(const char* name, GuiRenderer* guiRenderer) : Panel(name, guiRenderer)
{
	m_color = glm::vec4(0.6, 0.6, 0.6, 1.0f);
}

Button::Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size) : Panel(name, guiRenderer, position, size)
{
	m_color = glm::vec4(0.6, 0.6, 0.6, 1.0f);
}

Button::Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent) : Panel(name, guiRenderer, position, size, parent)
{
	m_color = glm::vec4(0.6, 0.6, 0.6, 1.0f);
}

bool Button::HandleInput(Input* input)
{
	m_buttonState = ButtonState::NORMAL;

	glm::vec2 mousePos = input->GetMouseAbsPos() / 2.0f; // Hardcoded scaling factor. although the scale factor should be different for the UI
	//printf("Mouse pos: %f, %f\n", mousePos.x, mousePos.y);

	if (IsInBounds(mousePos))
	{
		m_buttonState = ButtonState::HOVERED;

		if (input->IsMouseButtonHeld(SDL_BUTTON_LEFT))
		{
			m_buttonState = ButtonState::PRESSED;
		}
		else if (input->IsMouseButtonPressed(SDL_BUTTON_LEFT))
		{
			printf("%s pressed\n", m_name.c_str());
			return true;
		}
	}

	return false;
}

void Button::Render()
{
	switch (m_buttonState)
	{
	case ButtonState::NORMAL:
		m_color = glm::vec4(0.6, 0.6, 0.6, 1.0f);
		break;
	case ButtonState::HOVERED:
		m_color = glm::vec4(0.7, 0.7, 0.7, 1.0f);
		break;
	case ButtonState::PRESSED:
		m_color = glm::vec4(0.55, 0.55, 0.55, 1.0f);
		break;
	case ButtonState::DISABLED:
		m_color = glm::vec4(0.6, 0.6, 0.6, .5f);
		break;
	default:
		break;
	}

	Panel::Render();
}
