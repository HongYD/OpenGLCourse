#include "Mesh.h"



Mesh::Mesh(float _vertices[])
{
	this->vertices.resize(36);
	memcpy(&this->vertices[0], _vertices, 36 * 8 * sizeof(float));
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures)
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
	setupMesh();

}

void Mesh::Draw(Shader * _shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			_shader->SetUniform1i("material.diffuse",0);
		}

		else if (textures[i].type == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			_shader->SetUniform1i("material.specular", 1);
		}	
	}
	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES,0,36);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

Mesh::~Mesh()
{
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6*sizeof(GL_FLOAT)));

	glBindVertexArray(0);

}
