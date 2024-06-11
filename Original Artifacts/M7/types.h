#pragma once
#include <glm/glm.hpp>
#include <string>

struct Vertex {
	glm::vec3 Position{0.0f, 0.0f, 0.0f};
	glm::vec3 Color{1.f, 1.f, 1.f};
	glm::vec2 UV{ 1.f, 1.f };
	glm::vec3 Normal{0.0f, 0.0f, 0.f};
};

const glm::vec3 blue{ 0.f,0.f, 1.f };
const glm::vec3 pink{ 1.f,0.8f, 0.8f };
const glm::vec3 green{ 0.f,1.f, 0.f };
const glm::vec3 yellow{ 1.f,1.f, 0.5f };
const glm::vec3 orange{ 1.f,0.3f, 0.2f };
const glm::vec3 red{ 05.f,0.f, 0.2f };
const glm::vec3 white{ 1.f, 1.f, 1.f };
const glm::vec3 gray{ 0.5f, 0.5f, 0.5f };

