#pragma once
#include <vector>
#include "types.h"

class Box
{
public:
	Box(float width, float height, float z, float X, float Y, glm::vec3 color);
	std::vector<Vertex>& get_vertices();
	std::vector<uint32_t>& get_indices();
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 pos = { 0.0f, 0.0f, 4.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };
};

