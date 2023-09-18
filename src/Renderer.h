#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Vertex.h"

#include <vector>

class Renderer
{
public:
	Renderer() = default;
	~Renderer() {}

	void Init();
	void SetProjection(unsigned int screenWidth, unsigned int screenHeight);
	void Render();
	void Dispose();

	// TODO dont use a vector for this. waste when we can just allocate however much memory we need into a buffer
	void AddVerticesToBatch(const std::vector<Vertex> vertices, const glm::vec3& worldPosition);
	void AddIndicesToBatch(const std::vector<unsigned int> indices, const int indicesToAdd);

private:
	void CreateShaderProgram();
	void CreateRenderData();

	void CheckError();

	GLuint m_shaderProgram;

	std::vector<Vertex> m_vertexBuffer;
	std::vector<unsigned int> m_indexBuffer;
	int m_indicesToAdd = 0;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

};