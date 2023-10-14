#include "Button.h"

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

//void Button::Render()
//{
//	Render();
//}
