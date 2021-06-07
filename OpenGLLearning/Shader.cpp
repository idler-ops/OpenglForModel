/*
Shader��
������ʼ��shader������vertex shader��fragment shader�ĳ����벢���ж�Ӧ�Ĵ������롢���ӳ�Ϊ������program
�������������ʱ����ļ��
��װ��glUseProgram(ID)���ú�������Ⱦѭ����ʹ�ã����ڽ�ID��Ӧ��shader program�󶨵���ǰ����Ⱦ״̬��
installs the program object specified by program as part of current rendering state
��װ��3����shader����uniform�����ĺ�����1f��1i��3f��
��һ��enum��ΪSlot��ר���������ִ���shader�����ݸ�diffuse��specular������Texture��ͼ��
*/

#include "Shader.h"

using namespace std;

Shader::~Shader(){}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
	ifstream vertexFile, fragmentFile;
	stringstream vertexSStream, fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::badbit || ifstream::failbit);
	fragmentFile.exceptions(ifstream::badbit || ifstream::failbit);
	try {
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw exception("Open file error\n");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, nullptr);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, nullptr);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const exception &ex) {
		printf(ex.what());
	}
}

void Shader::checkCompileErrors(unsigned int id, string type) {
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(id, 512, nullptr, infoLog);
			cout << "Shader compile error: " << infoLog << endl;
		}
	}
	else {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, nullptr, infoLog);
			cout << "Program link error: " << infoLog << endl;
		}
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::test() {
	printf("Shader created successfully.\n");
}

void Shader::SetUniform3f(const char * paramNameString, glm::vec3 param) {
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);
}

void Shader::SetUniform1f(const char * paramNameString, float param) {
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::SetUniform1i(const char * paramNameString, int slot) {
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}
