#include "Camera.h"


Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup) 
{
	//Camera������������Camera��Forward������������������������
	//Camera�Լ���Up������Forward������˸ոյõ����Լ���������
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
	//�����������λ�ã������Ŀ��λ�ã�����������λ��
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

