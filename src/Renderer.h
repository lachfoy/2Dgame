#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Vertex.h"

#include <vector>

class SpriteEntity;

class RenderObject
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
	GLuint texture;
};

class RenderObjectCompare
{
public:
	bool operator()(const RenderObject& obj1, const RenderObject& obj2) const
	{
		return obj1.texture < obj2.texture;
	}
};

class Renderer
{
public:
	Renderer() = default;
	~Renderer() {}

	void Init();
	void SetProjection(unsigned int screenWidth, unsigned int screenHeight);
	void RenderBackground();
	void RenderSprites();
	void Dispose();

	// TODO dont use a vector for this. waste when we can just allocate however much memory we need into a buffer
	void AddVerticesToBatch(const std::vector<Vertex>& vertices, const glm::vec3& worldPosition);
	void AddIndicesToBatch(const unsigned int* indices, const int indexCount, const int indicesToAdd);
	void AddRenderObjectToBatch(std::vector<Vertex> vertices, std::vector<unsigned int> indices, GLuint texture);
	void SubmitRenderObjects();

private:
	void CreateShaderProgram();
	void CreateRenderData();

	void CheckError();

	GLuint m_shaderProgram;

	// keep this in the actual "render sprites" call. dont hold onto it 
	std::vector<Vertex> m_vertexBuffer;
	std::vector<unsigned int> m_indexBuffer;
	int m_indicesToAdd = 0;
	//
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::vector<RenderObject> m_renderObjectBatch;

	GLuint m_tempTexture;

};