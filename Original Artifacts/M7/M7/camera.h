#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	enum class MoveDirection {
		Forward,
		Backward,
		Left,
		Right,
		Up,
		Down
	};
	Camera() = default;
	explicit Camera(int width, int height, glm::vec3 initalPosition = {0, 0, -2.f}, bool isPerspective = true);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void setAspectRatio(int width, int height) {
		_width = width;
		_height = height;
	}
	void switchCamMode() {
		_isPerspective = !_isPerspective;
	}
	void MoveCamera(MoveDirection dir, float amount);
	void RotateBy(float yaw, float pitch);
	void IncrementZoom(float amount);
	glm::vec3 getPosition();
private:
	//Camera attributes
	int _width{};
	int _height{};
	//Position of the camera
	glm::vec3 _position{};
	//Target the camera is looking at
	glm::vec3 _lookDirection{};
	//Knowing where is up and down
	glm::vec3 _upDirection{ 0.f, 1.f, 0.f };

	float _fieldOfView{ 75.f };
	bool _isPerspective{ true };
	
	float _nearClip{ 0.1f };
	float _farClip{ 100.f };
	
	//camera mouse values
	float _yaw{-90.f}; //left and right
	float _pitch{}; //up & down

	void recalculateVectors();
	float clamp(float value, float min, float max);
};

