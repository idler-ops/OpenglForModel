/*
Camera��
������ʼ�����λ�ã����뵱ǰ���λ�ú� ��ǡ�ƫ���ǡ������� �������Ϸ������� / ��ǰ���λ�ú� ���ֱ��Ŀ������ꡢ�����Ϸ���������
Ҫ�����Forward��������һ���� �����ָ��Ŀ����������������ǰ������������Right�������ҷ�����������Up�������Ϸ���������
ע�⣬�������߾���Ҫ��һ��
��װ�˻�ȡViewMatrix�Ĺ��ܣ���������������ϵת�����������ϵ��view space��
��װ�˸��������������λ���������Լ����λ�õĹ��ܣ�����ͨ��qweasd�����ٿ�����ƶ�����ת�ӽǣ�����ת�ӽ�Ҫע�����������⣩
*/

#include "Camera.h"

Camera::~Camera() {}

//��������Ϊcameraλ�á��뿴��Ŀ���λ�á������Ϸ���ָ�������
Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup) {
	Position = _position;
	WorldUp = _worldup;
	Forward = glm::normalize(_target - _position);	//��һ��
	Right = glm::normalize(glm::cross(Forward, WorldUp));	//���
	Up = glm::normalize(glm::cross(Right, Forward));
}

//����target�����ɸ�����ŷ���ǡ�pitchΪ��ǣ������ϣ���x�ᣩ��yawΪƫ���ǣ����Ͽ�˳ʱ�룬��y�ᣩ��rollΪ�����ǣ���z�ᣬ��z����������ʱ�룩
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

glm::mat4 Camera::GetViewMatrix() {			//������cameraλ�ã�����Ŀ���λ�ã������Ϸ���
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
