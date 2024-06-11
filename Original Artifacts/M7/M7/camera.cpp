#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>


Camera::Camera(int width, int height,glm::vec3 initialPosition, bool isPerspective)
{
	setAspectRatio(width, height);
	_isPerspective = isPerspective;
	_position = initialPosition;
	//_lookDirection = {-1.f * initialPosition};
	_lookDirection = { 0.f, 0.f, 1.f };
	recalculateVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_position, _position +  _lookDirection, _upDirection);
}

glm::mat4 Camera::getProjectionMatrix()
{
	auto aspectRatio = (float)_width / (float)_height;
	if (_isPerspective) {
		return glm::perspective(glm::radians(_fieldOfView), aspectRatio, _nearClip, _farClip);
	}
	else {
		return glm::ortho(-aspectRatio, aspectRatio, -1.f, 1.f, _nearClip, _farClip);
	}
}

void Camera::MoveCamera(MoveDirection direction, float amount)
{
	glm::vec3 moveDirection;

	glm::vec3 Y = glm::vec3(1.0f, 0.0f, 0.0f);
	switch (direction){
			case Camera::MoveDirection::Forward: {
				moveDirection = _lookDirection;
				break;
				}
			case Camera::MoveDirection::Backward: {
				moveDirection = -_lookDirection;
				break;
			}
			case Camera::MoveDirection::Left: {
				moveDirection = -glm::normalize(glm::cross(_lookDirection, _upDirection));
				break;
			}
			case Camera::MoveDirection::Right: {
				moveDirection = glm::normalize(glm::cross(_lookDirection, _upDirection));
				break;
			}
		/*
		   if upDirection = (0,1,0) == X,Y,Z meaning, up is the Y axis
		   then (1, 0, 0) makes X our up and down, so using the right-left moves works
		*/
			case Camera::MoveDirection::Up: {
				moveDirection = -glm::normalize(glm::cross(_lookDirection, Y));
				break;
			}
			case Camera::MoveDirection::Down: {
				moveDirection = glm::normalize(glm::cross(_lookDirection, Y));
				break;
			}
			default:
				break;
	}
	_position += moveDirection * amount;
}

void Camera::RotateBy(float yaw, float pitch)
{
	_yaw += yaw;
	_pitch += pitch;

	_pitch = clamp(_pitch, -89.0f, 89.0f);
	recalculateVectors();
}

void Camera::IncrementZoom(float amount)
{
	amount *= -2;
	_fieldOfView += amount;
	_fieldOfView = clamp(_fieldOfView, 1.f, 75.f);
}

glm::vec3 Camera::getPosition()
{
	return this->_position;
}

void Camera::recalculateVectors(){
	_lookDirection = glm::normalize(
		glm::vec3(
			std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)),
			std::sin(glm::radians(_pitch)),
			std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch))
		)
	);

	auto rightDirection = glm::normalize(glm::cross(_lookDirection, _upDirection));
	//_upDirection = glm::normalize(glm::cross(rightDirection, _lookDirection));
}

float Camera::clamp(float value, float min, float max)
{
	if (value > max) return max;
	if (value < min) return min;
	return value;
}
