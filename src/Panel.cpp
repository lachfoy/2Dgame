#include "Panel.h"

#include "GuiRenderer.h"
#include "Input.h"

Panel::Panel(const char* name, GuiRenderer* guiRenderer) : m_guiRenderer(guiRenderer)
{
	m_name = name;
	m_color = glm::vec4(0.3, 0.3, 0.3, 0.0f);
}

Panel::Panel(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size) : m_guiRenderer(guiRenderer), m_relativePosition(position), m_size(size)
{
	m_name = name;
	m_color = glm::vec4(0.3, 0.3, 0.3, 0.0f);
}

Panel::Panel(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent) : m_guiRenderer(guiRenderer), m_relativePosition(position), m_size(size), m_parent(parent)
{
	m_name = name;
	m_color = glm::vec4(0.3, 0.3, 0.3, 0.0f);
}

bool Panel::HandleInput(Input* input)
{
	// return true to consume the input
	// return false to allow the input to be read by other panels

	//if (input->IsKeyPressed(SDL_SCANCODE_Z))
	//{
	//	printf("%s consumed input\n", m_name.c_str());
	//	return true;
	//}

	return false;
}

void Panel::Render()
{
	glm::vec2 position = GetAbsolutePosition();
	glm::vec2 size = GetSize();

	// build the index and vertex vecs
	// Create the mesh data
	// This should be handled by a different class though
	m_vertexVec.clear();
	m_vertexVec.push_back({ glm::vec2(position.x, position.y + size.y), glm::vec2(0.0f, 1.0f) });
	m_vertexVec.push_back({ position + size, glm::vec2(1.0f, 1.0f) });
	m_vertexVec.push_back({ position, glm::vec2(0.0f, 0.0f) });
	m_vertexVec.push_back({ glm::vec2(position.x + size.x, position.y), glm::vec2(1.0f, 0.0f) });

	m_indexVec.clear();
	m_indexVec.push_back(0);
	m_indexVec.push_back(1);
	m_indexVec.push_back(2);
	m_indexVec.push_back(1);
	m_indexVec.push_back(3);
	m_indexVec.push_back(2);
	
	GuiRenderObject guiRenderObject = GuiRenderObject(
		&m_vertexVec,
		&m_indexVec,
		&m_color
	);

	m_guiRenderer->AddGuiRenderObject(guiRenderObject);
}

void Panel::DebugRenderBounds()
{
	// render outline
	glm::vec2 position = GetAbsolutePosition();
	glm::vec2 size = GetSize();

	m_guiRenderer->AddDebugLine(glm::vec2(position.x, position.y + size.y), position + size); // bl to br
	m_guiRenderer->AddDebugLine(position + size, glm::vec2(position.x + size.x, position.y)); // br to tr
	m_guiRenderer->AddDebugLine(glm::vec2(position.x + size.x, position.y), position); // tr to tl
	m_guiRenderer->AddDebugLine(position, glm::vec2(position.x, position.y + size.y)); // tl to bl
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
	glm::vec2 size = GetSize();
	glm::vec2 bottomRight = position + size;

	return point.x >= position.x && point.x <= bottomRight.x && point.y >= position.y && point.y <= bottomRight.y;
}

void Panel::SetColor(glm::vec4 color)
{
	m_color = color;
}

void Panel::SetPosition(glm::vec2 position)
{
	m_relativePosition = position;
}

void Panel::SetSize(glm::vec2 size)
{
	m_size = size;
}

void Panel::Center()
{
	// eugh
}

void Panel::AddChild(Panel* child)
{
	child->m_parent = this;
	m_children.push_back(child);
}
