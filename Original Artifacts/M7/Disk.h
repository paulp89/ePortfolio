#pragma once
#include "types.h"
#include <vector>
#include<tuple>

class Disk
{
public:
	Disk(float X = 0, float Y = 0);
	std::vector<Vertex>& get_vertices();
	std::vector<uint32_t>& get_indices();
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::tuple<float, float> rotate(std::tuple<float, float> point);
};