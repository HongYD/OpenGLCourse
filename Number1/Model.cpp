#include "Model.h"

Model::Model(std::string const & path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader * _shader)
{
	for (unsigned int  i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(_shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0,path.find_last_of('\\'));
	//std::cout<<"Model Load Success!!!"<<" : "<< directory << std::endl;
	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode * _node, const aiScene * _scene)
{
	//std::cout << _node->mName.data << std::endl;
	for (unsigned int i = 0; i < _node->mNumMeshes; i++)
	{
		aiMesh* curMesh= _scene->mMeshes[_node->mMeshes[i]];
		meshes.push_back(processMesh(curMesh,_scene));
	}
	for (unsigned int i = 0; i < _node->mNumChildren; i++)
	{
		processNode(_node->mChildren[i], _scene);
	}


}

Mesh Model::processMesh(aiMesh * _mesh, const aiScene * _scene)
{
	std::vector<Vertex>tempVertices;
	std::vector<unsigned int>tempIndices;
	std::vector<Texture>tempTexture;

	glm::vec3 tempVec;
	for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
	{
		Vertex tempVertex;

		tempVertex.Position.x = _mesh->mVertices[i].x;
		tempVertex.Position.y = _mesh->mVertices[i].y;
		tempVertex.Position.z = _mesh->mVertices[i].z;

		tempVertex.Normal.x = _mesh->mNormals[i].x;
		tempVertex.Normal.y = _mesh->mNormals[i].y;
		tempVertex.Normal.z = _mesh->mNormals[i].z;

		if (_mesh->mTextureCoords[0])
		{
			tempVertex.TexCoords.x = _mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = _mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tempVertex.TexCoords = glm::vec2(0, 0);
		}

		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < _mesh->mFaces[i].mNumIndices; j++)
		{
			tempIndices.push_back(_mesh->mFaces[i].mIndices[j]);
		}
		
	}

	return Mesh(tempVertices, tempIndices, {});
}
