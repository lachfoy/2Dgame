#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Panel.h"

enum class ButtonState
{
	NORMAL,
	HOVERED,
	PRESSED,
	DISABLED
};

class Button : public Panel
{
public:
	Button(const char* name, GuiRenderer* guiRenderer);
	Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size);
	Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent);
	~Button() = default;

	virtual bool HandleInput(Input* input);

	void Render() override;

private:
	ButtonState m_buttonState = ButtonState::NORMAL;

};
