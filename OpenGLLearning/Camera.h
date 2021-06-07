#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldup);
	Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float SenseX = 0.01f;
	float SenseY = 0.01f;
	float SenseZ = 0.01f;

	float speedZ = 0.0f;
	float speedX = 0.0f;
	float speedY = 0.0f;

	glm::mat4 GetViewMatrix();

	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPosition();

private:
	void UpdateCameraVectors();
};

