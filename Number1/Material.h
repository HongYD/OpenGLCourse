#pragma once
#include"Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	//颜色参数
	Shader* shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	//光照贴图参数
	unsigned int diffuseMapID;
	unsigned int specularMapID;
	unsigned int emissionMapID;

	Material()=default;
	Material(Shader* _shader,glm::vec3 _ambient,glm::vec3 _diffuse,glm::vec3 _specular,float _shininess);
	Material(Shader* _shader,unsigned int _emission, glm::vec3  _ambient, unsigned int _diffuse, unsigned int _specular, float _shininess);
	~Material();
};

