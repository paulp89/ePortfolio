#include "Hat.h"



Hat::Hat(float hat_size, float hat_height, glm::vec3 hat_color)
{
	size = hat_size;
	height = hat_height;
	color = hat_color;
	float offset = 1.5;

	glm::vec3 corner_normals{ 0.f, 1.f, 0.f };

	//box
	Vertex cube_front0 = { {size*offset, height, size*offset}, color, { 1.f, 1.f } , { 0, 0, 1.f }, };
	Vertex cube_front1 = { {size, 0, size}, color, { 1.f, 0.f } , { 0, 0, 1.f }, };
	Vertex cube_front2 = { {-size, 0, size}, color,{ 0.f, 0.f }, { 0, 0, 1.f }, };
	Vertex cube_front3 = { {-size*offset, height, size * offset}, color, { 0.f, 1.f } , { 0, 0, 1.f } };

	Vertex cube_back0 = { {-size * offset, height, -size * offset}, color, { 1.f, 1.f },{ 0, 0, -1.f } };
	Vertex cube_back1 = { {-size, 0, -size}, color,{ 1.f, 0.f } ,{ 0, 0, -1.f } };
	Vertex cube_back2 = { {size, 0, -size}, color,{ 0.f, 0.f },  { 0, 0, -1.f } };
	Vertex cube_back3 = { {size * offset, height, -size * offset}, color,{ 0.f, 1.f } , { 0, 0, -1.f } };

	Vertex cube_left0 = { {-size * offset, height, size * offset}, color, { 1.f, 1.f },  { -1.f, 0, 0.f } };
	Vertex cube_left1 = { {-size, 0, size}, color, { 1.f, 0.f },  { -1.f, 0, 0.f } };
	Vertex cube_left2 = { {-size, 0, -size}, color,{ 0.f, 0.f } , { -1.f, 0, 0.f } };
	Vertex cube_left3 = { {-size * offset, height, -size * offset}, color,{ 0.f, 1.f }, { -1.f, 0, 0.f } };

	Vertex cube_right0 = { {size * offset, height, -size * offset}, color,{ 1.f, 1.f } , { 1.f, 0, 0.f } };
	Vertex cube_right1 = { {size, 0, -size}, color,{ 1.f, 0.f }, { 1.f, 0, 0.f } };
	Vertex cube_right2 = { {size, 0, size}, color,{ 0.f, 0.f }, { 1.f, 0, 0.f } };
	Vertex cube_right3 = { {size * offset, height, size * offset}, color,{ 0.f, 1.f }, { 1.f, 0, 0.f } };
	
	Vertex cube_bottom0 = { {size, 0, size}, color, { 1.f, 1.f }, { 0.f, -1.f, 0.f }, };
	Vertex cube_bottom1 = { {size, 0, -size}, color,{ 1.f, 0.f }, { 0.f, -1.f, 0.f } };
	Vertex cube_bottom2 = { {-size, 0, -size}, color, { 0.f, 0.f }, { 0.f, -1.f, 0.f } };
	Vertex cube_bottom3 = { {-size, 0, size}, color,{ 0.f, 1.f },  { 0.f, -1.f, 0.f } };
	
	
	Vertex cube_top0 = { {size*offset, height, -size*offset}, color, { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
	Vertex cube_top1 = { {size*offset, height, size * offset}, color, { 1.f, 0.f } , { 0.f, 1.f, 0.f } };
	Vertex cube_top2 = { {-size*offset, height, size * offset}, color, { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex cube_top3 = { {-size*offset, height, -size * offset}, color, { 0.f, 1.f }, { 0.f, 1.f, 0.f } };


	//HAT BRIM
	//brim front
	Vertex brim_front = { {size, 0, size}, {color}, { 1.f, 1.f } ,{ 0.f, 1.f, 0.f },};
	Vertex brim_front1 = { {size, 0, size * 3}, {color}, { 1.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_front2 = { {-size, 0, size * 3}, {color}, { 0.f, 0.f },{ 0.f, 1.f, 0.f } };
	Vertex brim_front3 = { {-size, 0, size}, {color}, { 0.f, 1.f },{ 0.f, 1.f, 0.f } };

	//brim back
	Vertex brim_back = { {size, 0, -size * 3}, {color}, { 1.f, 1.f } ,{ 0.f, 1.f, 0.f } };//right back 
	Vertex brim_back1 = { {size, 0, -size}, {color}, { 1.f, 0.f }, { 0.f, 1.f, 0.f } }; //right front 
	Vertex brim_back2 = { {-size, 0, -size}, {color}, { 0.f, 0.f }, { 0.f, 1.f, 0.f } }; //left front 
	Vertex brim_back3 = { {-size, 0, -size * 3}, {color}, { 0.f, 1.f }, { 0.f, 1.f, 0.f } };//left back

	//brim right
	Vertex brim_right = { {size * 3, 0, -size}, {color}, { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_right1 = { {size * 3, 0, size}, {color}, { 1.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_right2 = { {size, 0, size}, {color}, { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_right3 = { {size, 0, -size}, {color}, { 0.f, 1.f },{ 0.f, 1.f, 0.f } };

	//brim left
	Vertex brim_left = { {-size * 3, 0, -size}, {color}, { 1.f, 1.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_left1 = { {-size * 3, 0, size}, {color}, { 1.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_left2 = { {-size, 0, size}, {color}, { 0.f, 0.f }, { 0.f, 1.f, 0.f } };
	Vertex brim_left3 = { {-	size, 0, -size}, {color}, { 0.f, 1.f },{ 0.f, 1.f, 0.f } };


	//corners
	Vertex c0 = { {size, 0, size}, {color}, { 0.f, 0.f }, corner_normals };
	Vertex c1 = { {size, 0, size * 3}, {color}, { 0.5f, 1.f }, corner_normals };
	Vertex c2 = { {size * 3, 0, size}, {color}, { 1.f, 0.f },  corner_normals };

	Vertex c3 = { {-size, 0, size}, {color}, { 0.f, 0.f },corner_normals };
	Vertex c4 = { {-size, 0, size * 3}, {color},{ 0.5f, 1.f },corner_normals };
	Vertex c5 = { {-size * 3, 0, size}, {color},{ 1.f, 0.f },corner_normals };

	Vertex c6 = { {-size * 3, 0, -size}, {color}, { 0.f, 0.f },corner_normals};
	Vertex c7 = { {-size, 0, -size * 3}, {color}, { 0.5f, 1.f },corner_normals};
	Vertex c8 = { {-size, 0, -size}, {color},{ 1.f, 0.f }, corner_normals};

	Vertex c9 = { {size * 3, 0, -size}, {color}, { 0.f, 0.f }, corner_normals};
	Vertex c10 = { {size, 0, -size * 3}, {color}, { 0.5f, 1.f }, corner_normals};
	Vertex c11 = { {size, 0, -size}, {color},{ 1.f, 0.f }, corner_normals};

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

		//brim
		24, 25, 27 ,
		25, 26, 27,

		28, 29, 31,
		29, 30, 31,

		32, 33, 35,
		33, 34, 35,

		36, 37, 39,
		37, 38, 39,
		//corner 1
		40, 41, 42,
		//corner 2
		43, 44, 45,
		//corner 3
		46, 47, 48,
		//corner 4
		49, 50, 51
	};
	//box front
	vertices.push_back(cube_front0);
	vertices.push_back(cube_front1);
	vertices.push_back(cube_front2);
	vertices.push_back(cube_front3);
	//box back
	vertices.push_back(cube_back0);
	vertices.push_back(cube_back1);
	vertices.push_back(cube_back2);
	vertices.push_back(cube_back3);
	//box left
	vertices.push_back(cube_left0);
	vertices.push_back(cube_left1);
	vertices.push_back(cube_left2);
	vertices.push_back(cube_left3);
	//box right
	vertices.push_back(cube_right0);
	vertices.push_back(cube_right1);
	vertices.push_back(cube_right2);
	vertices.push_back(cube_right3);
	//box top
	vertices.push_back(cube_top0);
	vertices.push_back(cube_top1);
	vertices.push_back(cube_top2);
	vertices.push_back(cube_top3);
	//box bottom
	vertices.push_back(cube_bottom0);
	vertices.push_back(cube_bottom1);
	vertices.push_back(cube_bottom2);
	vertices.push_back(cube_bottom3);

	//brim front
	vertices.push_back(brim_front);
	vertices.push_back(brim_front1);
	vertices.push_back(brim_front2);
	vertices.push_back(brim_front3);
	
	//brim back
	vertices.push_back(brim_back);
	vertices.push_back(brim_back1);
	vertices.push_back(brim_back2);
	vertices.push_back(brim_back3);

	//brim right
	vertices.push_back(brim_right);
	vertices.push_back(brim_right1);
	vertices.push_back(brim_right2);
	vertices.push_back(brim_right3);

	//brim right
	vertices.push_back(brim_left);
	vertices.push_back(brim_left1);
	vertices.push_back(brim_left2);
	vertices.push_back(brim_left3);

	//corner 1
	vertices.push_back(c0);
	vertices.push_back(c1);
	vertices.push_back(c2);
	//corner 2
	vertices.push_back(c3);
	vertices.push_back(c4);
	vertices.push_back(c5);
	//corner 3
	vertices.push_back(c6);
	vertices.push_back(c7);
	vertices.push_back(c8);
	//corner 4
	vertices.push_back(c9);
	vertices.push_back(c10);
	vertices.push_back(c11);

}

std::vector<Vertex>& Hat::get_vertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Hat::get_indices()
{
	return this->indices;
}