#include "Box.h"


Box::Box(float width, float height, float z, float X, float Y, glm::vec3 color)
{
	/*
		top right
		bottom right
		bottom left
		top left
	*/
	//front
	height = height + Y;
	Vertex cube_front0 = { {X+width, height, z}, color, { 1.f, 1.f } , { 0, 0, 1.f }, };
	Vertex cube_front1 = { {X+width, Y, z}, color, { 1.f, 0.f } , { 0, 0, 1.f }, };
	Vertex cube_front2 = { {X, Y, z}, color,{ 0.f, 0.f }, { 0, 0, 1.f }, };
	Vertex cube_front3 = { {X, height, z}, color, { 0.f, 1.f } , { 0, 0, 1.f } };
	//back
	Vertex cube_back0 = { {X, height, -z}, color, { 1.f, 1.f },{ 0, 0, -1.f } };
	Vertex cube_back1 = { {X, Y, -z}, color,{ 1.f, 0.f } ,{ 0, 0, -1.f } };
	Vertex cube_back2 = { {X+width, Y, -z}, color,{ 0.f, 0.f },  { 0, 0, -1.f } };
	Vertex cube_back3 = { {X+width, height, -z}, color,{ 0.f, 1.f } , { 0, 0, -1.f } };
	//left
	Vertex cube_left0 = { {X, height, z}, color, { 1.f, 1.f },  { -1.f, 0, 0.f } };
	Vertex cube_left1 = { {X, Y, z}, color, { 1.f, 0.f },  { -1.f, 0, 0.f } };
	Vertex cube_left2 = { {X, Y, -z}, color,{ 0.f, 0.f } , { -1.f, 0, 0.f } };
	Vertex cube_left3 = { {X, height, -z}, color,{ 0.f, 1.f }, { -1.f, 0, 0.f } };
	//right
	Vertex cube_right0 = { {X + width, height, -z}, color,{ 1.f, 1.f } , { 1.f, 0, 0.f } };
	Vertex cube_right1 = { {X + width, Y, -z}, color,{ 1.f, 0.f }, { 1.f, 0, 0.f } };
	Vertex cube_right2 = { {X + width, Y, z}, color,{ 0.f, 0.f }, { 1.f, 0, 0.f } };
	Vertex cube_right3 = { {X + width, height, z}, color,{ 0.f, 1.f }, { 1.f, 0, 0.f } };
	//bottom
	Vertex cube_bottom0 = { {X + width, Y, z}, color, { 1.f, 1.f }, { 0.f, -1.f, 0.f }, };
	Vertex cube_bottom1 = { {X +width, Y, -z}, color,{ 1.f, 0.f }, { 0.f, -1.f, 0.f } };
	Vertex cube_bottom2 = { {X, Y, -z}, color, { 0.f, 0.f }, { 0.f, -1.f, 0.f } };
	Vertex cube_bottom3 = { {X, Y, z}, color,{ 0.f, 1.f },  { 0.f, -1.f, 0.f } };
	//top
	Vertex cube_top0 = { {X + width, height, -z}, color, { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
	Vertex cube_top1 = { {X + width, height, z}, color, { 1.f, 0.f } , { 0.f, 1.f, 0.f } };
	Vertex cube_top2 = { {X, height, z}, color, { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex cube_top3 = { {X, height, -z}, color, { 0.f, 1.f }, { 0.f, 1.f, 0.f } };

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
		23, 22, 21
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

std::vector<Vertex>& Box::get_vertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Box::get_indices()
{
	return this->indices;
}