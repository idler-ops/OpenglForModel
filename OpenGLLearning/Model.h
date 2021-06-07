//ģ�ͣ�����Ҫ����node�Ĳ㼶��ϵ���縸��node�������ܰ�����������������������ȡ��������Ⱦ
#pragma once

#include "Mesh.h"
#include <iostream>
#include <vector>
#include <string>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Shader.h"

class Model
{
public:
	Model(std::string path);
	~Model();
	std::vector<Mesh> meshes;
	std::string directory;
	void Draw(Shader *shader);

private:
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

