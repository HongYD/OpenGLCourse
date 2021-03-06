#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<Windows.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"stb_image.h"
#include"Shader.h"
#include"Camera.h"
#include"Material.h"
#include"LightDirectional.h"
#include"LightPoint.h"
#include"LightSpot.h"
#include"Mesh.h"
#include"Model.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
float lastX, lastY;
bool firstMouse = true;
//实例化相机类
//Camera camera(glm::vec3(0.0, 0.0, 3.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0,1.0f,0));
unsigned int LoadImageToGPU(const char* filename, GLint internalformat, GLenum format, int textureslot);
#pragma region CameraDeclare
Camera camera(glm::vec3(0.0, 0.0, 3.0f), glm::radians(2.0f), glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0));
#pragma endregion
#pragma region light declare
LightDirectional light (glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), 0.0, 0.0),glm::vec3(1.0f,1.0f,1.0f));
LightPoint lightpoint0 (glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(1.0f,1.0f,1.0f));
LightPoint lightpoint1 (glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
LightPoint lightpoint2 (glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0));
LightPoint lightpoint3 (glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0, 0.0f, 1.0f));



LightSpot lightspot = LightSpot(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), glm::radians(0.0f), glm::radians(0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

#pragma endregion light declare

//float vertices[] = {
//	//第一个三角形
//	-0.5f, -0.5f, 0.0f,//右上 //0
//	0.5f, -0.5f, 0.0f,//右下  //1
//	0.0f,  0.5f, 0.0f,//左上  //2
//
//	//第二个三角形
//	0.5f, -0.5f, 0.0f,//右下
//	0.0f, 0.5f, 0.0f,//左下
//	0.8f,0.8f,0.0f//左上      //3
//};

//float vertices[] = {
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

#pragma region ModelData

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 2, // 第一个三角形
	0,2,3  // 第二个三角形
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

//如果利用索引值，就叫index buffer,或element buffer
//上图所示0，1，2构成地一个三角形 2，1，3构成第二个三角形


int main(int argc,char* argv[])
{
	std::string exePath = argv[0];
	//std::cout <<exePath.substr(0,exePath.find_last_of('\\'))+"\\Model\\nanosuit\\nanosuit.obj" << std::endl;


	#pragma region OpenAWindow	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Fail to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	//system("pause");
	//return 0;

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "Init GlEW Failed" << endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
#pragma endregion OpenAWindow

	#pragma region InitShaderProgramm
	Shader* testshader = new Shader("vertexSource.shader", "fragmentSource.shader");
	#pragma endregion InitShaderProgramm

	#pragma region Init Material
	//直接输入颜色的方法
	//Material* myMaterial = new Material(testshader,glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),64.0f);
	//利用光照贴图的方法
	Material* myMaterial = new Material(testshader,LoadImageToGPU("matrix.jpg",GL_RGB,GL_RGB,Shader::EMISSION) ,glm::vec3(1.0f, 1.0f, 1.0f), LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE), LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR), 32.0f);
	#pragma endregion Init Material

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//VBO:从CPU来的模型的序列化数据，将所有顶点坐标，法向量等等全部序列化成一个字符串
	//VAO:解析VBO,将VBO序列化的数据继续再解析成顶点，法向量...
	//VAO=Array Buffer+Element Buffer
	//这里进行VAO声明，glGenVertexArrays()的返回值是一个ID,存在int VAO中
	//这个函数其实可以一次性声明多个VAO glGenVertexArrays(大于1的数，数组首地址)
	#pragma region Init And Load to VAO and VBO and EBO
	
	//Mesh cube(vertices);
	Model testmodel(exePath.substr(0, exePath.find_last_of('\\')) + "\\Model\\nanosuit\\nanosuit.obj");
	
	
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	////声明VBO,与VAO同理
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	////绑定VAO与VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices ,GL_STATIC_DRAW);


	////创建vertex Shader，已经在Shader.h中封装，这里注释
	////unsigned int vertexShader;
	////vertexShader = glCreateShader(GL_VERTEX_SHADER);
	////glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	////glCompileShader(vertexShader);

	///*int  success_vertext;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertext);
	//if (!success_vertext)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}*/

	////创建fragment Shader，已经在Shader.h中封装，这里注释
	////unsigned int fragmentShader;
	////fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	////glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	////glCompileShader(fragmentShader);

	///*int  success_fragment;
	//char infoLog2[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_fragment);
	//if (!success_fragment)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog2);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	//}*/
	//
	////链接Shader，已在Shader.h中封装，注释这里
	////unsigned int shaderProgram;
	////shaderProgram = glCreateProgram();
	////glAttachShader(shaderProgram, vertexShader);
	////glAttachShader(shaderProgram, fragmentShader);
	////glLinkProgram(shaderProgram);

	////glUseProgram(shaderProgram);

	////glDeleteShader(vertexShader);
	////glDeleteShader(fragmentShader);


	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	////定点属性,在第零号栏位，每隔三个位置输送一笔资料，类型是GL_Float,不需要归一化。每隔6个挖一次，起始偏移量为0
	//glEnableVertexAttribArray(0); 

	////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//////定点属性,在第零号栏位，每隔三个位置输送一笔资料，类型是GL_Float,不需要归一化.
	////glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	////定点属性,在第零号栏位，每隔三个位置输送一笔资料，类型是GL_Float,不需要归一化.
	//glEnableVertexAttribArray(2);

	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	////定点属性,在第零号栏位，每隔三个位置输送一笔资料，类型是GL_Float,不需要归一化.
	//glEnableVertexAttribArray(3);

	#pragma endregion Init And Load to VAO and VBO and EBO


	#pragma region Init And Load Textures
	//unsigned int TexBufferA = LoadImageToGPU("pic.jpg",GL_RGB,GL_RGB,0);
	//unsigned int TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);
	#pragma endregion Init And Load Textures
	//glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	
	//calculate transformation matrix
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
	//trans = glm::rotate(trans, (float)glfwGetTime()/*glm::radians(0.01f)*/, glm::vec3(0.0, 0.0, 1.0f));
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));
	#pragma region Prepare MVP matrices
	glm::mat4 modelMat;
	modelMat = glm::rotate(modelMat,glm::radians(-55.0f),glm::vec3(1.0f,0.0,0.0));

	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, glm::vec3(0.0, 0.0, -3.0f));
	//viewMat = camera.GetViewMatrix();

	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);

	#pragma endregion Prepare MVP matrices

	#pragma region rendering loop
	while (!glfwWindowShouldClose(window))
	{
				
		ProcessInput(window);//在这一帧进行按键获取

		/*在这个区间进行输入渲染指令*/
		//Clear Screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		


		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//还得再Bind一次，因为OpenGL是状态机，之前有可能状态已经改变了。

		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 1; i++)
		{
			//Set Material->Shader Programm
			testshader->use();

			//下面四行可有可无，因为之前已经绑定过了
			//Set Material->Texture
			/*glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuseMapID);
			glActiveTexture(GL_TEXTURE0+Shader::SPECULAR);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specularMapID);
			glActiveTexture(GL_TEXTURE0+Shader::EMISSION);
			glBindTexture(GL_TEXTURE_2D, myMaterial->emissionMapID);*/

			//Set Material->Uniform
			//glUniform1i(glGetUniformLocation(testshader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(testshader->ID, "ourFace"), 1);

			glm::mat4 modelMat2;
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);
			//先缩放，再旋转，最后位移
			//MT位移，MR旋转，MS缩放，V定点位置：
			//MT * MR * MS * V:执行的时候会“从右向左”，即先缩放，再旋转，最后位移
			//但是在OpenGL中，由于是栈调用，所以缩放的语句应该写在旋转语句之后
			//glm::mat4 trans;
			//trans = glm::translate(trans, glm::vec3(-0.0001f, 0.0, 0.0));
			//trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0.0, 0.0, 1.0f));
			//trans = glm::scale(trans, glm::vec3(1.0002f, 1.0002f, 1.0002f));
			//unsigned int transformLoc = glGetUniformLocation(testshader->ID, "transform");
			//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans))
			glm::mat4 model;
			model = glm::rotate(model, (float)glfwGetTime()* glm::radians(50.0f)*(i+1), glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));;
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "modelMat2"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniform3f(glGetUniformLocation(testshader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(testshader->ID, "ambientColor"), 0.2f, 0.2f, 0.2f);

			//加入平行光之后，这个lightPos就不需要了
			//glUniform3f(glGetUniformLocation(testshader->ID, "lightPos"), 10.0f, 10.0f, 5.0f);
			//glUniform3f(glGetUniformLocation(testshader->ID, "lightColor"), 1.0f, 1.0f, 1.0f);
			//glUniform3f(glGetUniformLocation(testshader->ID, "lightDir"), 10.0f, 10.0f, 5.0f);
			glUniform3f(glGetUniformLocation(testshader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			
			//光源设置
			//平行光源
			myMaterial->shader->SetUniform3f("lightD.pos", light.position);
			myMaterial->shader->SetUniform3f("lightD.color", light.color);
			myMaterial->shader->SetUniform3f("lightD.dirToLight", light.direction);

			//点光源1，点光源需要光源位置和衰减值参数
			myMaterial->shader->SetUniform3f("lightP0.pos", lightpoint0.position);
			myMaterial->shader->SetUniform3f("lightP0.color", lightpoint0.color);
			//衰减参数
			myMaterial->shader->SetUniform1f("lightP0.constant",lightpoint0.constant);
			myMaterial->shader->SetUniform1f("lightP0.linear",lightpoint0.linear);
			myMaterial->shader->SetUniform1f("lightP0.quadratic",lightpoint0.quadratic);

			//点光源2，点光源需要光源位置和衰减值参数
			myMaterial->shader->SetUniform3f("lightP1.pos", lightpoint1.position);
			myMaterial->shader->SetUniform3f("lightP1.color", lightpoint1.color);
			//衰减参数
			myMaterial->shader->SetUniform1f("lightP1.constant", lightpoint1.constant);
			myMaterial->shader->SetUniform1f("lightP1.linear", lightpoint1.linear);
			myMaterial->shader->SetUniform1f("lightP1.quadratic", lightpoint1.quadratic);

			//点光源3，点光源需要光源位置和衰减值参数
			myMaterial->shader->SetUniform3f("lightP2.pos", lightpoint2.position);
			myMaterial->shader->SetUniform3f("lightP2.color", lightpoint2.color);
			//衰减参数
			myMaterial->shader->SetUniform1f("lightP2.constant", lightpoint2.constant);
			myMaterial->shader->SetUniform1f("lightP2.linear", lightpoint2.linear);
			myMaterial->shader->SetUniform1f("lightP2.quadratic", lightpoint2.quadratic);

			//点光源4，点光源需要光源位置和衰减值参数
			myMaterial->shader->SetUniform3f("lightP3.pos", lightpoint3.position);
			myMaterial->shader->SetUniform3f("lightP3.color", lightpoint3.color);
			//衰减参数
			myMaterial->shader->SetUniform1f("lightP3.constant", lightpoint3.constant);
			myMaterial->shader->SetUniform1f("lightP3.linear", lightpoint3.linear);
			myMaterial->shader->SetUniform1f("lightP3.quadratic", lightpoint3.quadratic);

			//聚光灯
			myMaterial->shader->SetUniform3f("lightS.pos", lightspot.position);
			myMaterial->shader->SetUniform3f("lightS.color", lightspot.color);
			myMaterial->shader->SetUniform3f("lightS.dirToLight", lightspot.direction);
			//衰减参数
			myMaterial->shader->SetUniform1f("lightS.constant", lightspot.constant);
			myMaterial->shader->SetUniform1f("lightS.linear", lightspot.linear);
			myMaterial->shader->SetUniform1f("lightS.quadratic", lightspot.quadratic);
			myMaterial->shader->SetUniform1f("lightS.cosPhyInner", lightspot.cosPhyInner);
			myMaterial->shader->SetUniform1f("lightS.cosPhyOutter", lightspot.cosPhyOutter);

			
			//myMaterial->shader->SetUniform3f("lightDirUniform", lightspot.direction);

			//myMaterial->shader->SetUniform3f("lightPos", lightspot.position);
			//myMaterial->shader->SetUniform3f("lightColor", lightspot.color);


			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			//emission Map
			myMaterial->shader->SetUniform1i("material.emissionMap", Shader::EMISSION);
			//diffuse Map
			myMaterial->shader->SetUniform1i("material.diffuseMap", Shader::DIFFUSE);
			//specular Map
			myMaterial->shader->SetUniform1i("material.specularMap", Shader::SPECULAR);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

			
			////glUniform3f已经封装在了Shader.h中，所以这里注释
			//glUniform3f(glGetUniformLocation(testshader->ID, "material.ambient"), 1.0f,1.0f,1.0f);
			//glUniform3f(glGetUniformLocation(testshader->ID, "material.diffuse"), 1.0,1.0,1.0f);
			//glUniform3f(glGetUniformLocation(testshader->ID, "material.specular"), 0.0,1.0f,0.0);
			//glUniform1f(glGetUniformLocation(testshader->ID, "material.shininess"), 256.0f);
			

			//Set Model
			//glBindVertexArray(VAO);
			//每一次调用glDrawArray()就是一次所谓“Draw Call”
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//cube.Draw(myMaterial->shader);
			testmodel.Draw(myMaterial->shader);
		}
		
		


		//调用Uniform调整颜色
		//float timeValue = glfwGetTime();
		//float greeanValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(testshader->ID, "ourColor");
		//glUniform4f(vertexColorLocation, 0, greeanValue, 0, 1.0f);

		//glUseProgram(shaderProgram);

		//利用EBO根据定顶点的index画立方体
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		
		
		//glBegin(GL_POLYGON);
		//glColor3d(1.0, 0.0, 0.0);
		//glVertex3i(4, 5, 0);
		//glVertex3i(7, 5, 0);
		//glVertex3i(4, 3, 0);
		//glEnd();

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//Clean up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();//在下一帧进行对按键行为进行处理
		camera.UpdateCameraPos();
		#pragma endregion rendering loop
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

unsigned int LoadImageToGPU(const char* filename,GLint internalformat,GLenum format, int textureslot) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0+textureslot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, numChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename, &width, &height, &numChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed" << endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}

#pragma region InputDeclare
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	//W,S
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.SpeedZ = 0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.SpeedZ = -0.01f;
	}
	else
	{
		camera.SpeedZ = 0;
	}

	//D,A
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.SpeedX = -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.SpeedX = 0.01f;
	}
	else
	{
		camera.SpeedX = 0;
	}

	//Q,E
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.SpeedY = -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.SpeedY = 0.01f;
	}
	else
	{
		camera.SpeedY = 0;
	}

}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(deltaX, deltaY);

}
#pragma endregion


