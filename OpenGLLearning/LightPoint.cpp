/*
LightPoint类
点光源，需要注意光源位置和颜色，方向无意义，一般认为随距离平方级衰减
还包含了衰减函数（二次函数）的三个系数
*/

#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	position(_position),
	angles(_angles),
	color(_color) 
{
	constant = 1.0f;
	linear = 0.1f;
	quadratic = 0.001f;
}

LightPoint::~LightPoint() {}
