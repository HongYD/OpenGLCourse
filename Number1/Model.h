#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include"Mesh.h"
#include"Shader.h"


class Model
{
public:
	std::vector<Mesh> meshes;
	std::string directory;
	Model()=default;
	Model(std::string const &path);
	~Model();
	void Draw(Shader* _shader);

private:
	void loadModel(std::string path);
	void processNode(aiNode* _node, const aiScene* _scene);
	Mesh processMesh(aiMesh* _mesh, const aiScene* _scene);
};

