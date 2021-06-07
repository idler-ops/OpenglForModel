/*
Material�����ʣ���
����ʹ�øò��ʵ�shader�����ʵ�ambient��ȫ�ֹ��յ�ɫ�ʣ���diffuse���������texture����specular�����淴���texture����
shininess�����㾵�淴���ǿʱ��ָ��ϵ����Խ��ʱ���淴���Խ���У�
*/

#include "Material.h"

Material::Material(Shader *_shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, float _shininess) :
	shader(_shader),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular),
	shininess(_shininess)
{}

Material::~Material() {}
