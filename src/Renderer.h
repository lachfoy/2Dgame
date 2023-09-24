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
	void RenderSprites();
	void Dispose();

	// TODO dont use a vector for this. waste when we can just allocate however much memory we need into a buffer
	void AddVerticesToBatch(const std::vector<Vertex>& vertices, const glm::vec2& worldPosition);
	void AddIndicesToBatch(const unsigned int* indices, const int indexCount, const int indicesToAdd);

	void AddRenderObject(const RenderObject& renderObject);
	
	void RenderObjects();

	void FlushBatch();

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

	std::vector<RenderObject> m_renderObjects;

};