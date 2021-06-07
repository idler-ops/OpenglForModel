/*
LightDirectional类
平行光源，光源位置无意义，只需要注意方向（初始化时由三个旋转角确定）和颜色，无衰减
*/

#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	UpdateDirection();
}

void LightDirectional::UpdateDirection() {
	direction = glm::vec3(0.0f, 0.0f, 1.0f);	// pointing to z (forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;	//shader中需要知道的是从原点出发的方向（反方向）
}

LightDirectional::~LightDirectional() {}
