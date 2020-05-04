#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera()=default;
	Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup);
	~Camera();
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	glm::mat4 GetViewMatrix();
};
