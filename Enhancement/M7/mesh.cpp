#include "mesh.h"
#include <iostream>


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
{
	init(vertices, elements);

}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements, const glm::vec3& color)
{
	for ( auto& vertex: vertices)
	{
		vertex.Color = color;
	}
	init(vertices, elements);
}



void Mesh::Draw()
{
	//Bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);

	//Bind vertex array
	glBindVertexArray(_vertexArrayObject);

	//gl draw calls
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) {
	//create the triangle
	glGenVertexArrays(1, &_vertexArrayObject);
	glGenBuffers(1, &_vertexBufferObject);
	glGenBuffers(1, &_elementBufferObject);

	glBindVertexArray(_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint32_t), elements.data(), GL_STATIC_DRAW);

	//define vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Color)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, UV)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	elementCount = elements.size();
}