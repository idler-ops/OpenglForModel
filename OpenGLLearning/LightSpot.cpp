/*
LightPoint类
聚光源，需要注意光源位置、方向（初始化时由三个旋转角确定）和颜色，一般认为随距离平方级衰减
还包含了衰减函数（二次函数）的三个系数
除此之外额外需要注意从光线中心线往外的角度
*/

#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.0f;
	linear = 0.1f;
	quadratic = 0.001f;
	UpdateDirection();
}

void LightSpot::UpdateDirection() {
	direction = glm::vec3(0.0f, 0.0f, 1.0f);	// pointing to z (forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;	//shader中需要知道的是从原点出发的方向（反方向）
}

LightSpot::~LightSpot() {}

