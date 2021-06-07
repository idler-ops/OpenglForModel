/*
Shader类
包含初始化shader、输入vertex shader与fragment shader的程序码并进行对应的处理，编译、链接成为完整的program
包含编译或链接时出错的检查
封装了glUseProgram(ID)，该函数在渲染循环中使用，用于将ID对应的shader program绑定到当前的渲染状态机
installs the program object specified by program as part of current rendering state
封装了3个向shader传递uniform参数的函数（1f、1i、3f）
有一个enum名为Slot，专门用于区分传入shader、传递给diffuse和specular的纹理（Texture）图像
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
