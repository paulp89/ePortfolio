#pragma once
#include "types.h"
#include <vector>
#include<tuple>

class Cylinder
{
public:
	Cylinder(float height, float X, float Y, glm::vec3 color, bool bottom = true, bool top = true, bool brim = false);
	Cylinder(float height);
	std::vector<Vertex>& get_vertices();
	std::vector<uint32_t>& get_indices();
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::tuple<float, float> rotate(std::tuple<float, float> point);
};
