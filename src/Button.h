#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Panel.h"



class Button : public Panel
{
public:
	Button(const char* name, GuiRenderer* guiRenderer);
	Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size);
	Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent);
	~Button() = default;

	void Render() override;

private:
	

};
