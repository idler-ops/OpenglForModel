/*
Model类
用来处理.obj文件中的内部逻辑，总体上是一个scene和多个物件（这些物件之间有着层级关系）
以及这些物件各自的meshes（这些都以相同的方式存储在另一个结构中，可以通过物件aiNode的mMeshes【】找到其对应的mesh）
初始化时从scene的根物件mRootNode开始向下深度优先搜索遍历所有aiNode
*/

#include "Model.h"

Model::Model(std::string path)
{
	loadModel(path);
}

Model::~Model() {}

void Model::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);		//scene，必须是const
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp error." << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_not_of('\\'));
	std::cout << "Model loaded successfully!" << std::endl;
	std::cout << directory << std::endl;

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *curMesh = scene->mMeshes[node->mMeshes[i]];		//要转成我自己的Mesh类型，包含uv值、Normal值等等
		meshes.push_back(processMesh(curMesh, scene));
	}

	std::cout << node->mName.data << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> tempTexture;
	
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex tempVertex;
		
		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;
		
		tempVertex.Normal.x = mesh->mNormals[i].x;
		tempVertex.Normal.y = mesh->mNormals[i].y;
		tempVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	return Mesh(tempVertices, tempIndices, {});
}
