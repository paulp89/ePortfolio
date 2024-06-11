 #include "application.h"
#include <iostream>
#include <glm/glm.hpp>
#include "types.h"
#include "Cube.h"
#include "Box.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Disk.h"
#include <vector>
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"      // Image loading Utility functions
#include <fstream>



Application::Application(std::string WindowTitle, int width, int height)
{
	_application_name = WindowTitle;
	_width = width;
	_height = height;
	_camera = Camera{ width, height, {3.f, 3.f, 8.f}, true };
	_cameraLookSpeed = {0.15f, 0.15f};
}

void Application::Run()
{
	if (!openWindow()) {
		return;
	}
	_running = true;
	//setup scene
	setupScene();
	setupInputs();
	while (_running)
	{
		float currentTime = glfwGetTime();
		if (_lastFrameTime == -1.f) {
			_lastFrameTime = currentTime;
		}

		auto deltaTime = currentTime - _lastFrameTime;
		_lastFrameTime = currentTime;

		if (glfwWindowShouldClose(_window)) {
			_running = false;
			continue;
		}
		//update
		update(deltaTime);
		//draw
		draw();
	}
	glfwTerminate();
}

bool Application::openWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	_window = glfwCreateWindow(800, 600,_application_name.c_str(), nullptr, nullptr);

	if (!_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, (void*)this);

	//Resizing listeners
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow * window, int width, int height) {
		glViewport(0, 0, width, height);
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->_width = width;
		app->_height = height;
		app->_camera.setAspectRatio(width, height);
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}
	//Depth
	glEnable(GL_DEPTH_TEST);

	//Hide internal faces
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	return true;
}

void Application::setupScene()
{
	/*
		Generate objects
	*/

	float plane_size = 4;
	float plane_x = -2;
	float plane_y = 0;

	Plane plane = Plane(plane_size, plane_size, plane_x, plane_y, white);
	Mesh table = Mesh(plane.get_vertices(), plane.get_indices());

	Cylinder plate_base = Cylinder(1.3, 0, 0, red, true, false, true);
	Mesh plate = Mesh(plate_base.get_vertices(), plate_base.get_indices());

	float cup_small_height = 3.0f;
	float cup_big_height = 12;

	Cylinder cb = Cylinder(cup_small_height, 0, 0, red, true, true);
	Cylinder cm = Cylinder(cup_big_height, 0, 0, yellow, false, false);
	Cylinder ct= Cylinder(cup_small_height, 0, 0, red, true, true);

	Mesh cup_bottom = Mesh(cb.get_vertices(), cb.get_indices());
	Mesh cup_middle = Mesh(cm.get_vertices(), cm.get_indices());
	Mesh cup_top = Mesh(ct.get_vertices(), ct.get_indices());

	Box small_box = Box(1.2f, 1.57f, 0.2f, 3.5, 0.05, white);
	Mesh dayquil = Mesh(small_box.get_vertices(), small_box.get_indices(), white);
	
	//Set correct ids for textures
	table.id = 1;
	plate.id = 2;
	//plate_brim.id = 3;
	cup_bottom.id = 4;
	cup_middle.id = 5;
	cup_top.id = 4;
	dayquil.id = 6;

	//Last minute adjustments for cylinders
	//Couldn't figure out how to resize them from within the class
	float plate_size = 0.2f;
	float cup_size = 0.08;
	plate.Transform = glm::scale(
		glm::mat4(1), glm::vec3(plate_size, plate_size, plate_size)
	);
	plate.Transform = glm::translate(
		plate.Transform, glm::vec3(6.5, 0.05, 8)
	);

	cup_bottom.Transform = glm::scale(
		glm::mat4(1), glm::vec3(cup_size, cup_size, cup_size)
	);
	cup_bottom.Transform = glm::translate(
		cup_bottom.Transform, glm::vec3(1, 0.05, -2)
	);

	cup_middle.Transform = glm::scale(
		glm::mat4(1), glm::vec3(cup_size, cup_size, cup_size)
	);
	cup_middle.Transform = glm::translate(
		cup_middle.Transform, glm::vec3(1, 0.05+cup_small_height, -2)
	);


	cup_top.Transform = glm::scale(
		glm::mat4(1), glm::vec3(cup_size, cup_size, cup_size)
	);
	cup_top.Transform = glm::translate(
		cup_top.Transform, glm::vec3(1, 0.05 + cup_small_height + cup_big_height, -2)
	);

	
	meshes.push_back(table);
	meshes.push_back(plate);
	meshes.push_back(cup_bottom);
	meshes.push_back(cup_middle);
	meshes.push_back(cup_top);
	meshes.push_back(dayquil);




	for (auto& mesh : meshes) {
		if (mesh.id != 1) {
			mesh.Transform = glm::rotate(mesh.Transform, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		}
		if (mesh.id == 6) {
			mesh.Transform = glm::rotate(mesh.Transform, glm::radians(-20.0f), glm::vec3(0, 0, 1));
			mesh.Transform = glm::translate(mesh.Transform, glm::vec3(0, 0.25, 0.25));
		}
	}

	//Lights
	lightPos = {-2, 3.5, 0};
	back_light_pos = { 4, 3.5, 0 };
	glm::mat4 key_light_pos(1);
	Cube cube = Cube(0.2f, white);
	Cube cube3 = Cube(0.2f, white);
	Mesh light = Mesh(cube.get_vertices(), cube.get_indices());

	light.id = -1;
	light.Transform = glm::translate(key_light_pos, lightPos );
	meshes.push_back(light);

	Mesh back_light = Mesh(cube3.get_vertices(), cube3.get_indices());
	back_light.id = -1;
	back_light.Transform = glm::translate(key_light_pos, back_light_pos);
	meshes.push_back(back_light);


	//create vertex shaders	
	std::ifstream vs("shaders/texture.vert");
	std::ifstream fs("shaders/texture.frag");
	std::ifstream light_vs("shaders/simple.vert");
	std::ifstream light_fs("shaders/simple.frag");

	_shader = Shader(vs, fs);
	_lightShader = Shader(light_vs, light_fs);

	//generating textures
	generateTextures(tx_table, "textures/table_vectorized.png");
	generateTextures(tx_plate, "textures/plate.png");
	generateTextures(tx_disk, "textures/disk.jpg");
	generateTextures(tx_yellow, "textures/ase_gold.jpg");
	generateTextures(tx_metal, "textures/metal.jpg");
	generateTextures(tx_dayquil, "textures/orange.jpg");
}

void Application::generateTextures(unsigned int& texture, std::string file) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, STBI_rgb);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture ["<<file <<"]"<< std::endl;
	}
	stbi_image_free(data);
}

void Application::setupInputs() {
	glfwSetKeyCallback(_window, [](GLFWwindow * window, int key, int scancode, int action, int mods) {
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		switch (key) {
			case GLFW_KEY_ESCAPE: {
				if (action == GLFW_PRESS) {
					app->_running = false;
				}
				break;
				}

			default: break;
		}
		});

	glfwSetCursorPosCallback(_window, [](GLFWwindow * window, double x, double y) {
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->handleMouse(x, y);
		});


	glfwSetScrollCallback(_window, [](GLFWwindow * window, double x, double y) {
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->_camera.IncrementZoom(y);
		});

	glfwSetMouseButtonCallback(_window, [](GLFWwindow * window, int button, int action, int mods) {
		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		switch (button) {
			case GLFW_MOUSE_BUTTON_LEFT: {
				if (action == GLFW_PRESS) {
					app->color += 1;
					if (app->color > 2) {
						app->color = 0;
					}
				}
				break;
			}
			case GLFW_MOUSE_BUTTON_RIGHT: {
				if (action == GLFW_PRESS) {
					app->_camera.switchCamMode();
				}
				break;
			}
			case GLFW_MOUSE_BUTTON_MIDDLE: {
				if (action == GLFW_PRESS) {
					app->animation = !app->animation;
				}
				break;
			}
			default:
				break;
			}
		});
}

void Application::handleInput(float deltaTime) {
	auto amount = _moveSpeed * deltaTime;
	if (glfwGetKey(_window, GLFW_KEY_W)) {
		_camera.MoveCamera(Camera::MoveDirection::Forward, amount);
	}
	if (glfwGetKey(_window, GLFW_KEY_S)) {
		_camera.MoveCamera(Camera::MoveDirection::Backward, amount);
	}
	if (glfwGetKey(_window, GLFW_KEY_A)) {
		_camera.MoveCamera(Camera::MoveDirection::Left, amount);
	}
	if (glfwGetKey(_window, GLFW_KEY_D)) {
		_camera.MoveCamera(Camera::MoveDirection::Right, amount);
	}
	//UP & DOWN
	if (glfwGetKey(_window, GLFW_KEY_Q)) {
		_camera.MoveCamera(Camera::MoveDirection::Up, amount);
	}
	if (glfwGetKey(_window, GLFW_KEY_E)) {
		_camera.MoveCamera(Camera::MoveDirection::Down, amount);
	}
	//SHOW LIGHT SOURCE
	if (glfwGetKey(_window, GLFW_KEY_L)) {
		showCubes = !showCubes;
	}
}

void Application::handleMouse(double x, double y) {
	if (_firstMouse) {
		_lastMousePosition[0] = static_cast<float>(x);
		_lastMousePosition[1] = static_cast<float>(y);
		_firstMouse = false;
	}
	glm::vec2 moveAmount = { x - _lastMousePosition[0],  _lastMousePosition[1]  - y};

	_lastMousePosition[0] = static_cast<float>(x);
	_lastMousePosition[1] = static_cast<float>(y);
	
	_camera.RotateBy(moveAmount[0] * _cameraLookSpeed[0] , moveAmount[1] * _cameraLookSpeed[1]);
}

bool Application::update(float deltaTime)
{
	glfwPollEvents();
	handleInput(deltaTime);
	return false;
}

bool Application::draw()
{

	glm::vec3 light = green;
	if (color == 0) {
		light = white;
	}
	else if (color == 1) {
		light = red;
	}
	else if (color == 2) {
		light = green;
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	

	//camera
	glm::mat4 view = _camera.getViewMatrix();
	glm::mat4 projection = _camera.getProjectionMatrix();

	//shader
	Shader shader;

	for (auto& mesh : meshes) {

		if (mesh.id >= 0) {
			shader = _shader;
		}
		else {
			//shader = _lightShader;
			continue;
		}

		shader.Bind();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
	
		if (mesh.id >= 0) {
			glm::vec3 camPos = _camera.getPosition();
			shader.setVec3("lightPos", lightPos);
			shader.setVec3("lightPos2", back_light_pos);
			shader.setVec3("lightColor", light);
			shader.setVec3("objectColor", objectColor);
			shader.setVec3("viewPos", camPos);
		}

		if (mesh.id == 1) {
			glBindTexture(GL_TEXTURE_2D, tx_table);
		}

		if (mesh.id == 2) {
			glBindTexture(GL_TEXTURE_2D, tx_plate);
		}

		if (mesh.id == 3) {
			glBindTexture(GL_TEXTURE_2D, tx_disk);
		}

		if (mesh.id == 4) {
			glBindTexture(GL_TEXTURE_2D, tx_metal);
		}
		
		if (mesh.id == 5) {
			glBindTexture(GL_TEXTURE_2D, tx_yellow);
		}

		if (mesh.id == 6) {
			glBindTexture(GL_TEXTURE_2D, tx_dayquil);
		}

		

		//animation
		if (animation) {
			//mesh.Transform = glm::rotate(mesh.Transform, glm::radians(0.02f), glm::vec3(1, 0, 0));
		}
		shader.setMat4("model", mesh.Transform);
		//Draw the figure
		mesh.Draw();
	}
	
	glfwSwapBuffers(_window);
	return false;
}
