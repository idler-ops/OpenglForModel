/*
Camera类
包含初始化相机位置（输入当前相机位置和 扬角、偏航角、翻滚角 和世界上方向向量 / 当前相机位置和 相机直面目标的坐标、世界上方向向量）
要计算出Forward向量（归一化的 从相机指向目标的向量，即相机的前方向向量）、Right向量（右方向向量）、Up向量（上方向向量）
注意，上面三者均需要归一化
封装了获取ViewMatrix的功能，用来从世界坐标系转换到相机坐标系（view space）
封装了更新相机的三个单位方向向量以及相机位置的功能，用于通过qweasd和鼠标操控相机移动和旋转视角（但旋转视角要注意万向锁问题）
*/

#include "Camera.h"

Camera::~Camera() {}

//参数依次为camera位置、想看的目标的位置、世界上方向指向的向量
Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup) {
	Position = _position;
	WorldUp = _worldup;
	Forward = glm::normalize(_target - _position);	//归一化
	Right = glm::normalize(glm::cross(Forward, WorldUp));	//叉乘
	Up = glm::normalize(glm::cross(Right, Forward));
}

//不给target，换成给两个欧拉角。pitch为扬角（方向朝上，绕x轴），yaw为偏航角（从上看顺时针，绕y轴），roll为翻滚角（绕z轴，从z轴正方向看逆时针）
Camera::Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldup) {
	Position = _position;
	WorldUp = _worldup;
	Pitch = _pitch;
	Yaw = _yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix() {			//参数：camera位置，看的目标的位置，世界上方向
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * SenseY;
	Yaw -= deltaX * SenseX;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPosition() {
	Position += Forward * speedZ * SenseZ + Right * speedX * SenseX + Up * speedY * SenseY;
}
