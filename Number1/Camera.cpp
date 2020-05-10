#include "Camera.h"


Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup) 
{
	//Camera的右向量等于Camera的Forward向量叉乘世界坐标的向上向量
	//Camera自己的Up量等于Forward向量叉乘刚刚得到的自己的右向量
	Position = _position;
	WorldUp = _worldup;
	Forward = glm::normalize(_target - _position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	MouseSensitivity = 0.01f;
}

Camera::Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldup)
{
	Position = _position;
	WorldUp = _worldup;
	Pitch = _pitch;
	Yaw = _yaw;
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	MouseSensitivity = 0.01f;
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	//参数：照相机位置，看向的目标位置，世界坐标上位置
	return glm::lookAt(Position,Position+Forward,WorldUp);
}

void Camera::ProcessMouseMovement(float _deltaX, float _deltaY)
{

	Pitch += _deltaY*MouseSensitivity;
	Yaw += _deltaX*MouseSensitivity;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPos()
{
	Position += Forward*SpeedZ;
}

float Camera::lerp(float start, float end, float interporlate)
{

		return start + interporlate * (end - start);
	
}



void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

