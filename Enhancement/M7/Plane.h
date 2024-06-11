#pragma once
#include "types.h"
#include <vector>

class Plane
{
public:
	Plane(float width, float z, float X, float Y, glm::vec3 color);
	Plane(float size, glm::vec3 color);
	std::vector<Vertex>& get_vertices();
	std::vector<uint32_t>& get_indices();
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 pos = { 0.0f, 0.0f, 4.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };
};

