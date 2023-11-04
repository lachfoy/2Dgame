#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Vertex.h"
#include "Texture.h"
#include <vector>

typedef std::vector<Vertex> tVertexVec;
typedef std::vector<unsigned int> tIndexVec;

class GuiRenderObject
{
public:
	GuiRenderObject(tVertexVec* vertexVec, tIndexVec* indexVec, glm::vec4* color)
		: m_vertexVec(vertexVec), m_indexVec(indexVec), m_color(color) {}

	tVertexVec* GetVertexVec() const { return m_vertexVec; }
	tIndexVec* GetIndexVec() const { return m_indexVec; }
	glm::vec4* GetColor() const { return m_color; }
	
private:
	tVertexVec* m_vertexVec;
	tIndexVec* m_indexVec;
	glm::vec4* m_color;

};

//class GuiRenderObjectCompare
//{
//public:
//	bool operator()(const GuiRenderObject& obj1, const GuiRenderObject& obj2) const
//	{
//		return obj1.GetTexture() < obj2.GetTexture();
//	}
//};

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