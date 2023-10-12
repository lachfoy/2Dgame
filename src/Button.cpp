#include "Button.h"

Button::Button(const char* name, GuiRenderer* guiRenderer) : Panel(name, guiRenderer)
{
}

Button::Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size) : Panel(name, guiRenderer, position, size)
{
}

Button::Button(const char* name, GuiRenderer* guiRenderer, glm::vec2 position, glm::vec2 size, Panel* parent) : Panel(name, guiRenderer, position, size, parent)
{
}

void Button::Render()
{

}
