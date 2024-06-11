#include "Plane.h"
#include <iostream>


Plane::Plane(float size, float z, float X, float Y, glm::vec3 color)
{

	//top
	Vertex v0 = { {X + size*2, Y, -z}, color, { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
	Vertex v1 = { {X + size*2, Y, z}, color, { 1.f, 0.f } , { 0.f, 1.f, 0.f } };
	Vertex v2 = { {X, Y, z}, color, { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex v3 = { {X, Y, -z}, color, { 0.f, 1.f }, { 0.f, 1.f, 0.f } };

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	indices = {
		3, 1, 0,
		3, 2, 1
	};
}

Plane::Plane(float size, glm::vec3 color):Plane(size, size, 0, 0, color){
	
}

std::vector<Vertex>& Plane::get_vertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Plane::get_indices()
{
	return this->indices;
}