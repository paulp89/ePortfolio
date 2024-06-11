#include "Cube.h"



Cube::Cube(float cube_size, glm::vec3 cube_color)
{	
	size = cube_size;
	color = cube_color;

	//top
	Vertex cube_front0 = { {size, size, size}, color, { 1.f, 1.f } , { 0, 0, 1.f }, };
	Vertex cube_front1 = { {size, -size, size}, color, { 1.f, 0.f } , { 0, 0, 1.f }, };
	Vertex cube_front2 = { {-size, -size, size}, color,{ 0.f, 0.f }, { 0, 0, 1.f }, };
	Vertex cube_front3 = { {-size, size, size}, color, { 0.f, 1.f } , { 0, 0, 1.f } };

	Vertex cube_back0 = { {-size, size, -size}, color, { 1.f, 1.f },{ 0, 0, -1.f } };
	Vertex cube_back1 = { {-size, -size, -size}, color,{ 1.f, 0.f } ,{ 0, 0, -1.f } };
	Vertex cube_back2 = { {size, -size, -size}, color,{ 0.f, 0.f },  { 0, 0, -1.f } };
	Vertex cube_back3 = { {size, size, -size}, color,{ 0.f, 1.f } , { 0, 0, -1.f } };

	Vertex cube_left0 = { {-size, size, size}, color, { 1.f, 1.f },  { -1.f, 0, 0.f } };
	Vertex cube_left1 = { {-size, -size, size}, color, { 1.f, 0.f },  { -1.f, 0, 0.f } };
	Vertex cube_left2 = { {-size, -size, -size}, color,{ 0.f, 0.f } , { -1.f, 0, 0.f } };
	Vertex cube_left3 = { {-size, size, -size}, color,{ 0.f, 1.f }, { -1.f, 0, 0.f } };

	Vertex cube_right0 = { {size, size, -size}, color,{ 1.f, 1.f } , { 1.f, 0, 0.f } };
	Vertex cube_right1 = { {size, -size, -size}, color,{ 1.f, 0.f }, { 1.f, 0, 0.f } };
	Vertex cube_right2 = { {size, -size, size}, color,{ 0.f, 0.f }, { 1.f, 0, 0.f } };
	Vertex cube_right3 = { {size, size, size}, color,{ 0.f, 1.f }, { 1.f, 0, 0.f } };

	Vertex cube_bottom0 = { {size, -size, size}, color, { 1.f, 1.f }, { 0.f, -1.f, 0.f }, };
	Vertex cube_bottom1 = { {size, -size, -size}, color,{ 1.f, 0.f }, { 0.f, -1.f, 0.f } };
	Vertex cube_bottom2 = { {-size, -size, -size}, color, { 0.f, 0.f }, { 0.f, -1.f, 0.f } };
	Vertex cube_bottom3 = { {-size, -size, size}, color,{ 0.f, 1.f },  { 0.f, -1.f, 0.f } };

	Vertex cube_top0 = { {size, size, -size}, color, { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
	Vertex cube_top1 = { {size, size, size}, color, { 1.f, 0.f } , { 0.f, 1.f, 0.f } };
	Vertex cube_top2 = { {-size, size, size}, color, { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex cube_top3 = { {-size, size, -size}, color, { 0.f, 1.f }, { 0.f, 1.f, 0.f } };

	indices = {
		// Front
		3, 1, 0,
		3, 2, 1,
		// Back
		7, 5, 4,
		7, 6, 5,
		// Left
		11, 9, 8,
		11, 10, 9,
		// Right
		15, 13, 12,
		15, 14, 13,
		// Top
		19, 17, 16,
		19, 18, 17,
		//Bottom
		23, 21, 20,
		23, 22, 21,
	};

	vertices.push_back(cube_front0);
	vertices.push_back(cube_front1);
	vertices.push_back(cube_front2);
	vertices.push_back(cube_front3);
	vertices.push_back(cube_back0);
	vertices.push_back(cube_back1);
	vertices.push_back(cube_back2);
	vertices.push_back(cube_back3);
	vertices.push_back(cube_left0);
	vertices.push_back(cube_left1);
	vertices.push_back(cube_left2);
	vertices.push_back(cube_left3);
	vertices.push_back(cube_right0);
	vertices.push_back(cube_right1);
	vertices.push_back(cube_right2);
	vertices.push_back(cube_right3);
	vertices.push_back(cube_top0);
	vertices.push_back(cube_top1);
	vertices.push_back(cube_top2);
	vertices.push_back(cube_top3);
	vertices.push_back(cube_bottom0);
	vertices.push_back(cube_bottom1);
	vertices.push_back(cube_bottom2);
	vertices.push_back(cube_bottom3);
}

Cube::Cube(float cube_size, glm::vec3 cube_color, glm::vec3 cube_position)
{
	pos = cube_position;
	Cube(cube_size, cube_color);
}

std::vector<Vertex>& Cube::get_vertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Cube::get_indices()
{
	return this->indices;
}
