#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Vertex.h"

#include <vector>

class SpriteEntity;

typedef std::vector<Vertex> tVertexVec;
typedef std::vector<unsigned int> tIndexVec;

class RenderObject
{
public:
	RenderObject(tVertexVec* vertexVec, tIndexVec* indexVec, glm::vec2* worldPosition, GLuint texture)
		: m_vertexVec(vertexVec), m_indexVec(indexVec), m_worldPosition(worldPosition), m_texture(texture) {}

	tVertexVec* VertexVec() const { return m_vertexVec; }
	tIndexVec* IndexVec() const { return m_indexVec; }
	GLuint Texture() const { return m_texture; }
	glm::vec2* WorldPosition() const { return m_worldPosition; }

private:
	tVertexVec* m_vertexVec;
	tIndexVec* m_indexVec;
	GLuint m_texture;
	glm::vec2* m_worldPosition;

};

class RenderObjectCompare
{
public:
	bool operator()(const RenderObject& obj1, const RenderObject& obj2) const
	{
		return obj1.Texture() < obj2.Texture();
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
	void Dispose();

	void AddRenderObject(const RenderObject& renderObject);
	
	void RenderObjects();

	void FlushBatch();
	void ClearBatch();

private:
	void CreateShaderProgram();
	void CreateRenderData();

	void CheckError();

	GLuint m_shaderProgram;

	tVertexVec m_vertexBuffer;
	tIndexVec m_indexBuffer;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::vector<RenderObject> m_renderObjects;

};