#include<iostream>
#include<fstream>
#include<sstream>
#include"Shader.h"
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

		printf(vertexSource);
		printf(fragmentSource);

	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}


}