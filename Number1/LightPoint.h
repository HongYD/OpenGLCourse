#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
	glm::vec3 position;
	glm::vec3 color;
	float constant;
	float linear;
	float quadratic;
	LightPoint()=default;
	LightPoint(glm::vec3 _position, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();
};

