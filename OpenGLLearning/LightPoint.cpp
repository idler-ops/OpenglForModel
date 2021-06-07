/*
LightPoint��
���Դ����Ҫע���Դλ�ú���ɫ�����������壬һ����Ϊ�����ƽ����˥��
��������˥�����������κ�����������ϵ��
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