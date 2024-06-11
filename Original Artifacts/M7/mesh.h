#pragma once

#include <vector>
#include "types.h"
#include <glad/glad.h>

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, const glm::vec3& color);
	void Draw();
	glm::mat4 Transform{1.f};
	int id{ 0 };
private:
	void init(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);
	uint32_t elementCount{ 0 };
	GLuint _vertexBufferObject{};
	GLuint _shaderProgram{};
	GLuint _vertexArrayObject{};
	GLuint _elementBufferObject{};
};