#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include <vector>

#include <string>

struct UIVertex
{
	float x;
	float y;
	float u;
	float v;

	static UIVertex Make(float x, float y, float u, float v)
	{
		UIVertex vertex;
		vertex.x = x;
		vertex.y = y;
		vertex.u = u;
		vertex.v = v;
		return vertex;
	}
};

struct QuadEntry
{
	UIVertex vertices[4];
	unsigned int indices[6];
	glm::vec3 color;
	float alpha;
	Texture* texture;
};

class Font;
class GuiRenderer
{
public:
	GuiRenderer() = default;
	~GuiRenderer() {}

	void Init();
	void SetProjection(unsigned int screenWidth, unsigned int screenHeight);
	void Dispose();

	void AddQuadToBatch(float x, float y, float w, float h, glm::vec3 color, float alpha = 1.0f);
	void AddTexturedQuadToBatch(float x, float y, float w, float h, Texture* texture, glm::vec3 color, float alpha = 1.0f);

	void AddStringToBatch(std::string string, float x, float y, glm::vec3 color, Font* font, float alpha = 1.0f);

	void RenderQuads();


private:
	void FlushQuads();

	void CreateShaderProgram();
	void CreateRenderData();

	GLuint m_shaderProgram;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::vector<QuadEntry> m_quadEntries;
	std::vector<UIVertex> m_quadVertices;
	std::vector<unsigned int> m_quadIndices;

	GLint m_colorUniformLocation;
	GLint m_textureUniformLocation;

	Texture* m_utilTexture;

};