#pragma once
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;//Shader ProgramµÄID
	Shader()=default;
	Shader(const char* vertexPath, const char* fragmentPath);
	//~Shader();
	std::string vertexString;
	std::string fragmentString;

	const char* vertexSource;
	const char* fragmentSource;

	void use();
	void SetUniform3f(const char* paraNameString, glm::vec3 param);
	void SetUniform1f(const char* paraNameString,float param);
	void SetUniform1i(const char* paraNameString, int slot);
	enum Slot
	{
		EMISSION,
		DIFFUSE,
		SPECULAR
	};

private:
	void checkCompileErrors(unsigned int ID,std::string type);

};
