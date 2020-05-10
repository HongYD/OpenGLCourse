#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera()=default;
	Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup);
	Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 _worldup);
	~Camera();
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float MouseSensitivity;
	float SpeedZ = 0.0;
	float CamSpeed = 0.02f;

	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float _deltaX,float _deltaY);
	void UpdateCameraPos();
	static float lerp(float start, float end, float interporlate);
private:
	const float CamSpeedMax = 5.0f;
	void UpdateCameraVectors();
};

