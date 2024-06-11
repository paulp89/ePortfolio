#pragma once
#include <vector>
#include "types.h"

class Cube
{
public:
	Cube(float cube_size, glm::vec3 cube_color);
	Cube(float cube_size, glm::vec3 cube_color, glm::vec3 cube_position);
	std::vector<Vertex>& get_vertices();
	std::vector<uint32_t>& get_indices();
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 pos = {0.0f, 0.0f,0.0f};
	glm::vec3 color { 1.0f, 1.0f, 1.0f };
	float size;

};

