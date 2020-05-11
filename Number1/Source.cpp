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

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
float lastX, lastY;
bool firstMouse = true;
//ʵ���������
//Camera camera(glm::vec3(0.0, 0.0, 3.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0,1.0f,0));
unsigned int LoadImageToGPU(const char* filename, GLint internalformat, GLenum format, int textureslot);
#pragma region CameraDeclare
Camera camera(glm::vec3(0.0, 0.0, 3.0f), glm::radians(2.0f), glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0));
#pragma endregion

//float vertices[] = {
//	//��һ��������
//	-0.5f, -0.5f, 0.0f,//���� //0
//	0.5f, -0.5f, 0.0f,//����  //1
//	0.0f,  0.5f, 0.0f,//����  //2
//
//	//�ڶ���������
//	0.5f, -0.5f, 0.0f,//����
//	0.0f, 0.5f, 0.0f,//����
//	0.8f,0.8f,0.0f//����      //3
//};

//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
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

unsigned int indices[] = { // ע��������0��ʼ! 
	0, 1, 2, // ��һ��������
	0,2,3  // �ڶ���������
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

//�����������ֵ���ͽ�index buffer,��element buffer
//��ͼ��ʾ0��1��2���ɵ�һ�������� 2��1��3���ɵڶ���������


int main()
{
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//VBO:��CPU����ģ�͵����л����ݣ������ж������꣬�������ȵ�ȫ�����л���һ���ַ���
	//VAO:����VBO,��VBO���л������ݼ����ٽ����ɶ��㣬������...
	//VAO=Array Buffer+Element Buffer
	//�������VAO������glGenVertexArrays()�ķ���ֵ��һ��ID,����int VAO��
	//���������ʵ����һ�����������VAO glGenVertexArrays(����1�����������׵�ַ)
	#pragma region Init And Load to VAO and VBO and EBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//����VBO,��VAOͬ��
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//��VAO��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices ,GL_STATIC_DRAW);


	//����vertex Shader���Ѿ���Shader.h�з�װ������ע��
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	/*int  success_vertext;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertext);
	if (!success_vertext)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}*/

	//����fragment Shader���Ѿ���Shader.h�з�װ������ע��
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	/*int  success_fragment;
	char infoLog2[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_fragment);
	if (!success_fragment)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog2);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	}*/
	
	//����Shader������Shader.h�з�װ��ע������
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//glUseProgram(shaderProgram);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//��������,�ڵ������λ��ÿ������λ������һ�����ϣ�������GL_Float,����Ҫ��һ����ÿ��6����һ�Σ���ʼƫ����Ϊ0
	glEnableVertexAttribArray(0); 

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	////��������,�ڵ������λ��ÿ������λ������һ�����ϣ�������GL_Float,����Ҫ��һ��.
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//��������,�ڵ������λ��ÿ������λ������һ�����ϣ�������GL_Float,����Ҫ��һ��.
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	//��������,�ڵ������λ��ÿ������λ������һ�����ϣ�������GL_Float,����Ҫ��һ��.
	glEnableVertexAttribArray(3);

	#pragma endregion Init And Load to VAO and VBO and EBO


	#pragma region Init And Load Textures
	unsigned int TexBufferA = LoadImageToGPU("pic.jpg",GL_RGB,GL_RGB,0);
	unsigned int TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);
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
				
		ProcessInput(window);//����һ֡���а�����ȡ

		/*������������������Ⱦָ��*/
		//Clear Screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//������Bindһ�Σ���ΪOpenGL��״̬����֮ǰ�п���״̬�Ѿ��ı��ˡ�

		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 10; i++)
		{
			//Set Material->Shader Programm
			testshader->use();

			//�������п��п��ޣ���Ϊ֮ǰ�Ѿ��󶨹���
			//Set Material->Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, TexBufferA);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, TexBufferB);

			//Set Material->Uniform
			glUniform1i(glGetUniformLocation(testshader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(testshader->ID, "ourFace"), 1);

			glm::mat4 modelMat2;
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);
			//�����ţ�����ת�����λ��
			//MTλ�ƣ�MR��ת��MS���ţ�V����λ�ã�
			//MT * MR * MS * V:ִ�е�ʱ��ᡰ�������󡱣��������ţ�����ת�����λ��
			//������OpenGL�У�������ջ���ã��������ŵ����Ӧ��д����ת���֮��
			//glm::mat4 trans;
			//trans = glm::translate(trans, glm::vec3(-0.0001f, 0.0, 0.0));
			//trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0.0, 0.0, 1.0f));
			//trans = glm::scale(trans, glm::vec3(1.0002f, 1.0002f, 1.0002f));
			//unsigned int transformLoc = glGetUniformLocation(testshader->ID, "transform");
			//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans))
			glm::mat4 model;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f)*(i+1), glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));;
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "modelMat2"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniform3f(glGetUniformLocation(testshader->ID, "objColor"), 1.0f, 0.5f, 0.31f);
			glUniform3f(glGetUniformLocation(testshader->ID, "ambientColor"), 1.0f, 0.5f, 0.31f);
			glUniform3f(glGetUniformLocation(testshader->ID, "lightPos"), 10.0f, 10.0f, 5.0f);
			glUniform3f(glGetUniformLocation(testshader->ID, "lightColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(testshader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			

			//Set Model
			glBindVertexArray(VAO);
			//ÿһ�ε���glDrawArray()����һ����ν��Draw Call��
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		


		//����Uniform������ɫ
		//float timeValue = glfwGetTime();
		//float greeanValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(testshader->ID, "ourColor");
		//glUniform4f(vertexColorLocation, 0, greeanValue, 0, 1.0f);

		//glUseProgram(shaderProgram);

		//����EBO���ݶ������index��������
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
		glfwPollEvents();//����һ֡���ж԰�����Ϊ���д���
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


