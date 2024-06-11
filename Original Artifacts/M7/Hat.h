#pragma once
#include <vector>
#include "types.h"

class Hat
{
public:
	Hat(float hat_size, float hat_height, glm::vec3 hat_color);
	std::vector<Vertex>& get_vertices();
	std::vector<uint32_t>& get_indices();
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 pos = { 0.0f, 0.0f, 4.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };
	float size;
	float height{ size * 10};

};