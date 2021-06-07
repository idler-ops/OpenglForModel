/*
Mesh��������
����������Ŀɻ���ʵ�塣
�������㼯���������ꡢ����������Ӧ��ͼ���꣩����ͼ���ϡ�ָ�꣨indices������EBO��
�ÿɻ���ʵ�������Ҫд���VAO��VBO��EBO

�ڳ�ʼ��meshʱҪ���ú�Ҫʹ�õ�VAO��VBO��EBO�������ݰ�����Ҫ�ĸ�ʽд������
��װ��Draw���������н�����������ͼ�󶨲�ͨ��uniform����shader��ͬʱ��VAO��ʹ��֮ǰ�Ѿ���VAO��VBO��EBOд�õ����ݿ�ʼ��ͼ�Σ������Σ�
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
			glActiveTexture(GL_TEXTURE0);					//����0�Ų�
			glBindTexture(GL_TEXTURE_2D, textures[i].id);	//��id��Ӧ��texture�󶨵�������Ĳ�
			shader->SetUniform1i("material.diffuse", 0);	//��Ӧ��shader��
		}
		else if (textures[i].type == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.specular", 1);
		}
	}
	glBindVertexArray(VAO);		//��VAO

//	glDrawArrays(GL_TRIANGLES, 0, 36);	//to be replaced
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//��ͼ�Σ�����������ͼ�Ρ�size�����͡�ƫ����
	
	glBindVertexArray(0);		//���
	glActiveTexture(GL_TEXTURE0);	//��texture��λ�ع�0��λ
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
