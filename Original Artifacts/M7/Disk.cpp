#include "Disk.h"



Disk::Disk(float X, float Y)
{
	Vertex center = Vertex{ {X, Y, 0}, white };
	vertices.push_back(center);

	std::tuple<float, float> left = std::tuple<float, float>(-1, -6);
	std::tuple<float, float> right = std::tuple<float, float>(1, -6);
	int sectors = 20;
	int v;

	//account for vertex from base disk
	v = vertices.size();
	left = std::tuple<float, float>(-1, -6);
	right = std::tuple<float, float>(1, -6);

	// cylinder body
	for (int i = 0; i < sectors; ++i)
	{
		float x = std::get<0>(left) + X;
		float y = std::get<1>(left) + Y;
		Vertex left_vertex = Vertex{ {x, y, 0} , red,  { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
		Vertex left_vertex_top = Vertex{ {x * 1.2, y * 1.2, 0}, red, { 1.f, 0.f } , { 0.f, 1.f, 0.f } };

		x = std::get<0>(right) + X;
		y = std::get<1>(right) + Y;
		Vertex right_vertex = Vertex{ {x, y, 0} };
		Vertex right_vertex_top = Vertex{ {x * 1.2, y * 1.2, 0} };
		/*
			top right
			bottom right
			bottom left
			top left
		*/
		vertices.push_back(right_vertex_top);
		vertices.push_back(right_vertex);

		vertices.push_back(left_vertex);
		vertices.push_back(left_vertex_top);
		//next face
		left = rotate(left);
		right = rotate(right);
	}
	//cylinder triangles
	for (int i = 0; i < sectors; ++i)
	{
		/*
		3, 1, 0,
		3, 2, 1
		*/

		indices.push_back(v + 3);
		indices.push_back(v + 1);
		indices.push_back(v);

		indices.push_back(v + 3);
		indices.push_back(v + 2);
		indices.push_back(v + 1);

		v += 4;
	}
}


std::vector<Vertex>& Disk::get_vertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Disk::get_indices()
{
	return this->indices;
}

std::tuple<float, float> Disk::rotate(std::tuple<float, float> point)
{
	const float PI = 3.1415926f;

	float dg = 18.f; //degree of rotation
	float r = (-dg * PI) / 180.0f;

	float a = std::get<0>(point);
	float b = std::get<1>(point);

	float x = cos(r) * a + b * sin(r);
	float y = -sin(r) * a + cos(r) * b;

	return std::tuple<float, float>(x, y);
}
