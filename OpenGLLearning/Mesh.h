#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "GL/glew.h"


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	//tangent��bitangent���������͸�����������Ϸ�����
};

struct Texture {
	unsigned int id;	//Ҫ��glGenTexture����һ�Ų��ʲ���stbi�⽫����load���ڴ�
	std::string type;
	std::string path;
};

class Mesh {
public:
	//��������
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(float vertices[]);
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
	~Mesh();
	void Draw(Shader *shader);
	//ÿ����������е���Ϣ

private:
	//��Ⱦ����
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

