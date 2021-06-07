#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	std::string vertexString;
	std::string fragmentString;
	const char *vertexSource;
	const char *fragmentSource;
	unsigned int ID;			//Shader program ID

	enum Slot {
		DIFFUSE,
		SPECULAR
	};

	Shader(const char *vertexPath, const char *fragmentPath);
	void use();
	void test();
	
	void SetUniform3f(const char *paramNameString, glm::vec3 param);
	void SetUniform1f(const char *paramNameString, float param);
	void SetUniform1i(const char *paramNameString, int slot);

	~Shader();

private:
	void checkCompileErrors(unsigned int id, std::string type);
};

