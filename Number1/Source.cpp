#define GLEW_STATIC
#include<iostream>
#include<Windows.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

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

float vertices[] = {
	// 位置              // 颜色
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // 顶部
	-0.5f,0.5f,0.0f,    0.8f,0.2f,0.2f
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 2, // 第一个三角形
	2,1,3  // 第二个三角形
};


//如果利用索引值，就叫index buffer,或element buffer
//上图所示0，1，2构成地一个三角形 2，1，3构成第二个三角形

const char* vertexShaderSource =
"#version 330 core                                        \n"
"layout(location = 0) in vec3 aPos;                       \n"
"layout(location = 1) in vec3 aColor;                     \n"
"out vec4 vertexColor;                                    \n"
"void main() {                                            \n"
"		gl_Position = vec4(aPos,1.0);                     \n"
"       vertexColor=vec4(aColor.x,aColor.y,aColor.z,1.0); \n"
"}                                                        \n";

const char* fragmentShaderSource =
"#version 330 core                              \n"
"in vec4 vertexColor;                           \n"
"uniform vec4 ourColor;                         \n"
"out vec4 FragColor;                            \n"
"void main() {                                  \n"
"    FragColor = vertexColor;}                  \n";

int main()
{
	Shader* testshader = new Shader("vertexSource.txt","fragmentSource.txt");
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//VBO:从CPU来的模型的序列化数据，将所有顶点坐标，法向量等等全部序列化成一个字符串
	//VAO:解析VBO,将VBO序列化的数据继续再解析成顶点，法向量...
	//VAO=Array Buffer+Element Buffer
	//这里进行VAO声明，glGenVertexArrays()的返回值是一个ID,存在int VAO中
	//这个函数其实可以一次性声明多个VAO glGenVertexArrays(大于1的数，数组首地址)
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//声明VBO,与VAO同理
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//绑定VAO与VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices ,GL_STATIC_DRAW);



	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*int  success_vertext;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertext);
	if (!success_vertext)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}*/

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*int  success_fragment;
	char infoLog2[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_fragment);
	if (!success_fragment)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog2);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	}*/
	
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//定点属性,在第零号栏位，每隔三个位置输送一笔资料，类型是GL_Float,不需要归一化。每隔6个挖一次，起始偏移量为0
	glEnableVertexAttribArray(0); 

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	//定点属性,在第零号栏位，每隔三个位置输送一笔资料，类型是GL_Float,不需要归一化.
	glEnableVertexAttribArray(1);



	//glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);//在这一帧进行按键获取

		/*在这个区间进行输入渲染指令*/
		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//还得再Bind一次，因为OpenGL是状态机，之前有可能状态已经改变了。

		
		
		float timeValue = glfwGetTime();
		float greeanValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0, greeanValue, 0, 1.0f);
		glUseProgram(shaderProgram);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();//在下一帧进行对按键行为进行处理
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		//glfwTerminate();
	}
}