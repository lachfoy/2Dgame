#pragma once

#include <glm/glm.hpp>
#include <string>

// base class for UI elements
// panels get constructed with a size and position
// store in a tree structure
// things outside a panel should get clipped by default

#include <vector>

#include "Vertex.h"
#include "Texture.h"

typedef std::vector<Vertex> tVertexVec;
typedef std::vector<unsigned int> tIndexVec;

class GuiRenderer;

class Panel
{
public:
	Panel(const char* name, GuiRenderer* guiRenderer);
	Panel(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size);
	Panel(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent);
	~Panel() = default;

	virtual void Render();
	void DebugRenderBounds();

	glm::vec2 GetAbsolutePosition() const;
	glm::vec2 GetSize() const;

	bool IsInBounds(glm::vec2 position);

	void SetColor(glm::vec4 color);

protected:
	std::string m_name;
	glm::vec2 m_size;

	glm::vec2 m_relativePosition; // top left
	Panel* m_parent = nullptr;

	GuiRenderer* m_guiRenderer;

	glm::vec4 m_color = glm::vec4(1.f, 1.f, 1.f, 1.f);

	tVertexVec m_vertexVec;
	tIndexVec m_indexVec;

};
