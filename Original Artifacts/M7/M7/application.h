#pragma once

//for abstraction

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mesh.h"
#include "shader.h"
#include "camera.h"


class Application {
public:
	Application(std::string WindowTitle, int width, int height);
	void Run();
private:
	Camera _camera;
	std::vector<Mesh> meshes;
	bool openWindow();
	void setupScene();
	void setupInputs();
	void handleInput(float deltaTime);
	void handleMouse(double x, double y);
	bool update(float deltaTime);
	bool draw();
	void generateTextures(unsigned int& texture, std::string file);
	std::string _application_name{};
	GLFWwindow* _window{ nullptr };
	int _width{};
	int _height{};
	bool _running{ false };
	Shader _shader;
	//camera move speed
	float _moveSpeed = { 10.f };
	bool _firstMouse = true;
	glm::vec2 _lastMousePosition{-1.f, -1.f};
	glm::vec2 _cameraLookSpeed{};
	float _lastFrameTime{ -1.f };
	int color = 0;
	bool animation{ false };
	//lightning
	bool showCubes = false;
	float _ambient{ 0.1f };
	glm::vec3 lightPos = { -0.5, 2.5, 0.4 };
	glm::vec3 back_light_pos = { 0.5, 2.5, 0.4 };
	glm::vec3 objectColor = { 1.f, 1.0f, 1.0f };
	Shader _lightShader;
	Shader _fillLightShader;
	//colors
	glm::vec3 green{ 0.f, 1.f, 0.f };
	glm::vec3 red{ 1.f, 0.f, 0.f };
	glm::vec3 white{ 1.f, 1.f, 1.f };
	//textures
	unsigned int tx_table{};
	unsigned int tx_plate{};
	unsigned int tx_disk{};
	unsigned int tx_yellow{};
	unsigned int tx_metal{};
	unsigned int tx_dayquil{};
};