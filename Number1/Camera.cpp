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
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	//�����������λ�ã������Ŀ��λ�ã�����������λ��
	return glm::lookAt(Position,Position+Forward,WorldUp);
}

