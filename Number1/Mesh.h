#pragma once
#include<string>
#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"



struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex>vertices;
	std::vector<unsigned int>indices;
	std::vector<Texture>textures;
	Mesh()=default;
	Mesh(float _vertices[]);
	Mesh(std::vector<Vertex>_vertices,std::vector<unsigned int>_indices,std::vector<Texture>_textures);
	void Draw(Shader* _shader);
	~Mesh();
private:
	unsigned VAO, VBO, EBO;
	void setupMesh();
};

