#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightDirectional
{
public:
	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	void UpdateDirection();
	~LightDirectional();
	glm::vec3 position;		//它在平行光源中没有意义，但要用于点光源和聚光源
	glm::vec3 angles;		//旋转欧拉角
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);	//旋转后的光线向量
	glm::vec3 color;
};
