#pragma once
#include<string>
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

private:
	void checkCompileErrors(unsigned int ID,std::string type);

};
