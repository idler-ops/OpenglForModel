/*
Mesh（网格）类
网格代表单个的可绘制实体。
它包含点集（顶点坐标、法向量、对应贴图坐标）、贴图集合、指标（indices，用于EBO）
该可绘制实体的数据要写入的VAO、VBO、EBO

在初始化mesh时要配置好要使用的VAO、VBO、EBO并将数据按照想要的格式写入其中
封装了Draw函数，其中将所有纹理贴图绑定并通过uniform传进shader，同时绑定VAO，使用之前已经在VAO、VBO、EBO写好的数据开始画图形（三角形）
*/

#include "Mesh.h"

Mesh::Mesh(float vertices[]) {
	this->vertices.resize(36);
	memcpy(&this->vertices[0], vertices, sizeof(float) * 8 * 36);

	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures) {
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
	
	setupMesh();
}

Mesh::~Mesh() {}

void Mesh::Draw(Shader *shader) {
	for (unsigned int i = 0; i < textures.size(); i++) {
		if (textures[i].type == "texture_diffuse") {
			glActiveTexture(GL_TEXTURE0);					//激活0号槽
			glBindTexture(GL_TEXTURE_2D, textures[i].id);	//将id对应的texture绑定到所激活的槽
			shader->SetUniform1i("material.diffuse", 0);	//对应到shader中
		}
		else if (textures[i].type == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.specular", 1);
		}
	}
	glBindVertexArray(VAO);		//绑定VAO

//	glDrawArrays(GL_TRIANGLES, 0, 36);	//to be replaced
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//画图形，参数：画的图形、size、类型、偏移量
	
	glBindVertexArray(0);		//解绑
	glActiveTexture(GL_TEXTURE0);	//让texture槽位回归0号位
}

void Mesh::setupMesh() {
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// to be continue
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

}
