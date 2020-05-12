
#include<iostream>
#include<fstream>
#include<sstream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;



	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);


	try
	{
		if (!vertexFile.is_open()||!fragmentFile.is_open())
		{
			throw exception("open file error");
		}
		vertexSStream << vertexFile.rdbuf();//从硬盘读入数据，存入到StringStream(String Buffer)
		fragmentSStream << fragmentFile.rdbuf();
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		this->checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		this->checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		this->checkCompileErrors(ID, "PROGRAM");
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		//printf(vertexSource);
		//printf(fragmentSource);

	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char * paraNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paraNameString), param.x,param.y,param.z);
}

void Shader::SetUniform1f(const char * paraNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paraNameString), param);
}

void Shader::SetUniform1i(const char * paraNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paraNameString), slot);
}


void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);
			cout << "Shader Compile Error: " << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "Program Linking Error: " << infoLog << endl;
		}
	}
}