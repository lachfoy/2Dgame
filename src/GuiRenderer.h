#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include <vector>

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
	glm::vec4 color;
	GLuint textureHandle;
};

class GuiRenderer
{
public:
	GuiRenderer() = default;
	~GuiRenderer() {}

	void Init();
	void SetProjection(unsigned int screenWidth, unsigned int screenHeight);
	void Dispose();

	void AddQuadToBatch(glm::vec2 position, glm::vec2 size, glm::vec4 color);

	void AddStringToBatch(glm::vec2 position, glm::vec2 size, glm::vec4 color);

	void RenderQuads();


private:
	void CreateShaderProgram();
	void CreateRenderData();

	void CheckError();

	GLuint m_shaderProgram;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::vector<QuadEntry> m_quadEntries;
	std::vector<UIVertex> m_quadVertices;
	std::vector<unsigned int> m_quadIndices;

};