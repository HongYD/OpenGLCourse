#pragma once
#include<string>
class Shader
{
public:
	Shader()=default;
	Shader(const char* vertexPath, const char* fragmentPath);
	//~Shader();
	std::string vertexString;
	std::string fragmentString;

	const char* vertexSource;
	const char* fragmentSource;
};
