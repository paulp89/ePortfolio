#include "Cylinder.h"
#include <iostream>

Cylinder::Cylinder(float height, float X, float Y, glm::vec3 color, bool bottom, bool top, bool brim)
{	
	Vertex center = Vertex{ {X, Y, 0}, color, {0.f, 0.f}, { 1.f, 1.f, 1.f } };
	vertices.push_back(center);

	std::tuple<float, float> left = std::tuple<float, float>(-1, -6);
	std::tuple<float, float> right = std::tuple<float, float>( 1, -6);
	int sectors = 20;
	int v = 2;

	//bottom vertices
	for (int i = 0; i < sectors; ++i)
	{
		float x = std::get<0>(left) + X;
		float y = std::get<1>(left) + Y;
		Vertex left_vertex = Vertex{ {x, y, 0}, color, {1.f, 1.f}, {1.f, 0.f, 1.f}};
		
		x = std::get<0>(right) + X;
		y = std::get<1>(right) + Y;
		Vertex right_vertex = Vertex{ {x, y, 0}, color, {1.f, 1.f}, { 1.f, 0.f, 1.f } };
		
		vertices.push_back(left_vertex);
		vertices.push_back(right_vertex);

		left = rotate(left);
		right = rotate(right);
	}
	//triangles
	for (int i = 0; i < sectors; i++)
	{
		indices.push_back(0);
		indices.push_back(v);
		indices.push_back(v - 1);
		v += 2;
	}
	
	
	if (not bottom) {
		vertices.clear();
		indices.clear();
	}


	//account for vertex from base disk
	v = vertices.size();
	left = std::tuple<float, float>(-1, -6);
	right = std::tuple<float, float>(1, -6);

	// cylinder body
	for (int i = 0; i < sectors; ++i)
	{
		float x = std::get<0>(left) + X;
		float y = std::get<1>(left) + Y;
		Vertex left_vertex = Vertex{ {x, y, 0} , color,  { -1.f, 0.f }, { 0.f, 1.f, 0.f } };
		Vertex left_vertex_top = Vertex{ {x, y, height}, color, { 0.f, 0.f } , { 0.f, 1.f, 0.f } };

		x = std::get<0>(right) + X;
		y = std::get<1>(right) + Y;
		Vertex right_vertex = Vertex{ {x, y, 0},  color,  { -1.f, 0.f }, { 0.f, 1.f, 0.f } };
		Vertex right_vertex_top = Vertex{ {x, y, height},  color,  { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
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
		
		indices.push_back(v+ 3);
		indices.push_back(v + 2);
		indices.push_back(v + 1);
		
		v += 4;
	}

	if (top) {
		//account for vertex from base disk + body
		center = Vertex{ {X, Y, height}, color };
		vertices.push_back(center);
		//triangles
		int zero = vertices.size() - 1;
		v = zero + 2;

		left = std::tuple<float, float>(-1, -6);
		right = std::tuple<float, float>(1, -6);

		//top vertices
		for (int i = 0; i < sectors; ++i)
		{
			float x = std::get<0>(left) + X;
			float y = std::get<1>(left) + Y;
			Vertex left_vertex = Vertex{ {x, y, height}, color, {0.f, 0.f} };

			x = std::get<0>(right) + X;
			y = std::get<1>(right) + Y;
			Vertex right_vertex = Vertex{ {x, y, height}, color, {0.f, 0.f} };

			vertices.push_back(left_vertex);
			vertices.push_back(right_vertex);

			left = rotate(left);
			right = rotate(right);
		}


		for (int i = 0; i < sectors; i++)
		{
			indices.push_back(zero);
			indices.push_back(v);
			indices.push_back(v - 1);
			v += 2;
		}
	}


	if (not brim) return;


	v = vertices.size();
	left = std::tuple<float, float>(-1, -6);
	right = std::tuple<float, float>(1, -6);

	// brim body
	for (int i = 0; i < sectors; ++i)
	{
		float x = std::get<0>(left) + X;
		float y = std::get<1>(left) + Y;
		Vertex left_vertex = Vertex{ {x, y, height} , color,  { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
		Vertex left_vertex_top = Vertex{ {x * 1.2, y * 1.2, height}, color, { 1.f, 0.f } , { 0.f, 1.f, 0.f } };

		x = std::get<0>(right) + X;
		y = std::get<1>(right) + Y;
		Vertex right_vertex = Vertex{ {x, y, height}, color };
		Vertex right_vertex_top = Vertex{ {x * 1.2, y * 1.2, height}, color};
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
	//brim triangles
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

Cylinder::Cylinder(float height = 5):Cylinder(height, 0, 0, white)
{
	
}


std::vector<Vertex>& Cylinder::get_vertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Cylinder::get_indices()
{
	return this->indices;
}

std::tuple<float, float> Cylinder::rotate(std::tuple<float, float> point)
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
