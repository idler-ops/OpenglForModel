/*
Material（材质）类
包含使用该材质的shader、材质的ambient（全局光照的色彩）、diffuse（漫反射的texture）、specular（镜面反射的texture）、
shininess（计算镜面反射光强时的指数系数，越大时镜面反射光越集中）
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
