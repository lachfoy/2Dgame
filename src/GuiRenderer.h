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
	GuiRenderObject(tVertexVec* vertexVec, tIndexVec* indexVec, glm::vec4 color)
		: m_vertexVec(vertexVec), m_indexVec(indexVec), m_color(color) {}

	tVertexVec* GetVertexVec() const { return m_vertexVec; }
	tIndexVec* GetIndexVec() const { return m_indexVec; }
	glm::vec4 GetColor() const { return m_color; }
	
private:
	tVertexVec* m_vertexVec;
	tIndexVec* m_indexVec;
	glm::vec4 m_color;

};

//class GuiRenderObjectCompare
//{
//public:
//	bool operator()(const GuiRenderObject& obj1, const GuiRenderObject& obj2) const
//	{
//		return obj1.GetTexture() < obj2.GetTexture();
//	}
//};

class GuiRenderer
{
public:
	GuiRenderer() = default;
	~GuiRenderer() {}

	void Init();
	void SetProjection(unsigned int screenWidth, unsigned int screenHeight);
	void Dispose();

	void AddQuadToBatch(glm::vec2 position, glm::vec2 size, glm::vec4 color);

	void AddGuiRenderObject(const GuiRenderObject& renderObject);
	
	void RenderObjects();

	void AddDebugLine(const glm::vec2& p1, const glm::vec2& p2);
	void RenderDebugLines();

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

	std::vector<GuiRenderObject> m_guiRenderObjects;

	// Debug lines
	GLuint m_debugShaderProgram;
	std::vector<glm::vec2> m_linePoints;
	GLuint m_lineVao;
	GLuint m_lineVbo;

};