#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cassert>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static const unsigned int kMaxSprites = 2000;

void Renderer::Init()
{
	CreateShaderProgram();
	CreateRenderData();

	// Load texture
	int imageWidth, imageHeight, nChannels;
	unsigned char* imageData = stbi_load("data/images/Wizard.png", &imageWidth, &imageHeight, &nChannels, 0); // IDK how to handle different paths ...
	const char* failureReason = stbi_failure_reason();
	if (failureReason)
	{
		std::cout << failureReason << "\n";
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(imageData);

	{
		// Load texture
		int imageWidth, imageHeight, nChannels;
		unsigned char* imageData = stbi_load("data/images/BlackMage.png", &imageWidth, &imageHeight, &nChannels, 0); // IDK how to handle different paths ...
		const char* failureReason = stbi_failure_reason();
		if (failureReason)
		{
			std::cout << failureReason << "\n";
		}

		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(imageData);
	}
}

void Renderer::SetProjection(unsigned int screenWidth, unsigned int screenHeight)
{
	glUseProgram(m_shaderProgram);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "u_projection"), 1, false, glm::value_ptr(projection));
}

void Renderer::RenderBackground()
{

}

void Renderer::RenderSprites()
{
	// Update the VBO with the new vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexBuffer.size() * sizeof(Vertex), m_vertexBuffer.data());

	// Update the EBO with the new index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indexBuffer.size() * sizeof(unsigned int), m_indexBuffer.data());

	// Bind the shader and VAO
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);

	// bind texture
	//glBindTexture(GL_TEXTURE_2D, m_tempTexture);

	// Use glDrawElements to render the elements
	glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, NULL);

	// Unbind the EBO and VBO (optional but recommended)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_vertexBuffer.clear();
	m_indexBuffer.clear();
	m_indicesToAdd = 0;
}

void Renderer::Dispose()
{
	m_vertexBuffer.clear();
	m_indexBuffer.clear();

	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	
	glDeleteProgram(m_shaderProgram);
}

void Renderer::AddVerticesToBatch(const std::vector<Vertex>& vertices, const glm::vec2& worldPosition)
{
	for (const auto& vertex : vertices)
	{
		Vertex v = vertex;
		v.position += worldPosition;
		m_vertexBuffer.push_back(v);
	}
}

void Renderer::AddIndicesToBatch(const unsigned int* indices, const int indexCount, const int indicesToAdd)
{
	for (int i = 0; i < indexCount; i++) {
		m_indexBuffer.push_back(indices[i] + m_indicesToAdd);
	}
	m_indicesToAdd += indicesToAdd;
}

void Renderer::AddRenderObject(const RenderObject& renderObject)
{
	m_renderObjects.push_back(renderObject);
}

void Renderer::RenderObjects()
{
	//std::sort(m_renderObjects.begin(), m_renderObjects.end(), RenderObjectCompare());

	std::vector<Vertex> currentVertexBatch; // Current vertex batch
	std::vector<unsigned int> currentIndexBatch; // Current index batch
	GLuint currentTexture = 0; // Initialize with a default texture value (assumes GLuint cannot be negative)

	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);

	for (const RenderObject& obj : m_renderObjects)
	{
		if (obj.Texture() != currentTexture)
		{
			// If a different texture is encountered, start a new batch
			if (!currentVertexBatch.empty())
			{
				glBindTexture(GL_TEXTURE_2D, currentTexture);

				// Flush
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				glBufferSubData(GL_ARRAY_BUFFER, 0, currentVertexBatch.size() * sizeof(Vertex), currentVertexBatch.data());
				
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, currentIndexBatch.size() * sizeof(unsigned int), currentIndexBatch.data());

				glDrawElements(GL_TRIANGLES, currentIndexBatch.size(), GL_UNSIGNED_INT, 0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindTexture(GL_TEXTURE_2D, 0);

				// Clear
				currentVertexBatch.clear();
				currentIndexBatch.clear();
			}
			currentTexture = obj.Texture();
		}

		// Append the m_vertexVec from the current RenderObject to the current vertex batch
		currentVertexBatch.insert(currentVertexBatch.end(), obj.VertexVec()->begin(), obj.VertexVec()->end());

		// Append the indices from the current RenderObject to the current index batch
		unsigned int vertexOffset = currentVertexBatch.size() - obj.VertexVec()->size();
		for (unsigned int index : *obj.IndexVec())
		{
			currentIndexBatch.push_back(index + vertexOffset);
		}
	}

	// Add the last batch (if any) to the result
	if (!currentVertexBatch.empty())
	{
		glBindTexture(GL_TEXTURE_2D, currentTexture);

		// Flush
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, currentVertexBatch.size() * sizeof(Vertex), currentVertexBatch.data());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, currentIndexBatch.size() * sizeof(unsigned int), currentIndexBatch.data());

		glDrawElements(GL_TRIANGLES, currentIndexBatch.size(), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Clear
		currentVertexBatch.clear();
		currentIndexBatch.clear();
	}

	glBindVertexArray(0);
	m_renderObjects.clear();
}

void Renderer::FlushBatch()
{
	//glBindTexture(GL_TEXTURE_2D, currentTexture);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, currentVertexBatch.size() * sizeof(Vertex), currentVertexBatch.data());
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, currentIndexBatch.size() * sizeof(unsigned int), currentIndexBatch.data());
	//
	//glDrawElements(GL_TRIANGLES, currentIndexBatch.size(), GL_UNSIGNED_INT, 0);
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::CreateShaderProgram()
{
	// Create the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	{
		const GLchar* vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec2 a_position;
			layout (location = 1) in vec2 a_texcoord;

			varying vec2 v_texcoord;

			uniform mat4 u_projection;

			void main()
			{
				gl_Position = u_projection * vec4(a_position, 0.0, 1.0);
				v_texcoord = a_texcoord;
			}
		)";

		glShaderSource(vertexShader, 1, &vertexSource, 0);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("Failed to compile vertex shader:\n%s\n", infoLog);
		}
	}

	// Create the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	{
		const GLchar* fragmentSource = R"(
			#version 330 core
			out vec4 out_color;

			in vec2 v_texcoord;

			uniform vec4 u_color;
			uniform sampler2D u_sampler;

			void main()
			{
				out_color = texture(u_sampler, v_texcoord);
				//out_color = vec4(1, 0, 1, 1);
			}
		)";
		
		glShaderSource(fragmentShader, 1, &fragmentSource, 0);
		glCompileShader(fragmentShader);

		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			printf("Failed to compile fragment shader:\n%s\n", infoLog);
		}
	}

	// Link the final shader program
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	int success;
	char info_log[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, info_log);
		printf("Failed to link shader:\n%s\n", info_log);
	}

	// No longer need these
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set up sampler ...just one for now
	glUseProgram(m_shaderProgram);
	GLint textureUniformLocation = glGetUniformLocation(m_shaderProgram, "u_sampler");
	assert(textureUniformLocation >= 0 && "Sampler does not exist");
	glUniform1i(textureUniformLocation, 0);
}

void Renderer::CreateRenderData()
{
	// VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, kMaxSprites * 4 * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

	// EBO
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, kMaxSprites * 6 * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);

	// Enable the vertex attribute arrays for position and texcoords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::CheckError()
{
	GLenum error = glGetError();
	if (error > 0) {
		switch (error)
		{
		case GL_INVALID_ENUM:
			printf("GL_INVALID_ENUM");
			break;
		case GL_INVALID_OPERATION:
			printf("GL_INVALID_OPERATION");
			break;
		case GL_INVALID_VALUE:
			printf("GL_INVALID_VALUE");
			break;
		default:
			break;
		}
		//assert(false);
	}
}
