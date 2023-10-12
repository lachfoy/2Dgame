#include "Panel.h"

Panel::Panel(const char* name, GuiRenderer* guiRenderer) : m_guiRenderer(guiRenderer)
{
	m_name = name;
}

Panel::Panel(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size) : m_guiRenderer(guiRenderer), m_relativePosition(position), m_size(size)
{
	m_name = name;
}

Panel::Panel(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent) : m_guiRenderer(guiRenderer), m_relativePosition(position), m_size(size), m_parent(parent)
{
	m_name = name;
}

void Panel::Render()
{
	glm::vec2 position = GetAbsolutePosition();
	glm::vec2 size = GetSize();

	//m_guiRenderer->AddQuadToBatch();
}

void Panel::DebugRenderBounds()
{
	// render outline

	glm::vec2 position = GetAbsolutePosition();
	glm::vec2 size = GetSize();


}

glm::vec2 Panel::GetAbsolutePosition() const
{
	if (m_parent)
	{
		return m_parent->GetAbsolutePosition() + m_relativePosition;
	}

	return m_relativePosition;
}

glm::vec2 Panel::GetSize() const
{
	return m_size;
}

bool Panel::IsInBounds(glm::vec2 point)
{
	glm::vec2 position = GetAbsolutePosition();
	glm::vec2 bottomRight = position + GetSize();

	return point.x >= position.x && point.x <= bottomRight.x && point.y >= position.y && point.y <= bottomRight.y;
}

void Panel::SetColor(glm::vec4 color)
{
	m_color = color;
}
