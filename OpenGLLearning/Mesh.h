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
	//tangent和bitangent，切向量和辅切向量，配合法向量
};

struct Texture {
	unsigned int id;	//要用glGenTexture产生一张材质并用stbi库将数据load进内存
	std::string type;
	std::string path;
};

class Mesh {
public:
	//网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(float vertices[]);
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
	~Mesh();
	void Draw(Shader *shader);
	//每个顶点可能有的信息

private:
	//渲染数据
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

