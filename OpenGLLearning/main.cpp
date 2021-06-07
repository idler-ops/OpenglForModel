//���ȿ��Լ�ֱ�Ӹ�ԭһ�»������ӵĹ���

#define GLEW_STATIC

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"


#pragma region Model Data
//10�����������ԭ�������λ�ƾ��롣����ֻ�ı�position
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

//���������EBO����ʱ����
unsigned int indices[] =
{
	0, 1, 2,
	2, 3, 0
};
#pragma endregion

#pragma region Camera Declare
//��ʼ���������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
#pragma endregion

#pragma region Light Declare
LightDirectional light(
	glm::vec3(1.0f, 1.0f, -1.0f), 
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f), 
	glm::vec3(1.0f, 1.0f, 1.0f));

LightPoint lightP0(
	glm::vec3(1.0f, 0.0f, 0.0f),								//���� 
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),	//�Ƕ�
	glm::vec3(1.0f, 0.0f, 0.0f));								//��ɫ
LightPoint lightP1(
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
LightPoint lightP2(
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f));
LightPoint lightP3(
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightSpot lightS(
	glm::vec3(0.0f, 8.0f, 0.0f), 
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f),		//�������������
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion

#pragma region Input Declare
bool firstMouse = true;		//����mouse callback
float lastX, lastY;			//��¼mouseλ�ñ仯

void processInput(GLFWwindow *window) {		//��¼�����İ����¼����Ա��������
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.speedZ = 10.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.speedZ = -10.0f;
	else
		camera.speedZ = 0.0f;
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.speedX = -10.0f;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.speedX = 10.0f;
	else
		camera.speedX = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	//�³�
		camera.speedY = -10.0f;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.speedY = 10.0f;
	else
		camera.speedY = 0.0f;
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {		//��׽����ƶ�
	if (firstMouse == true) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX = xPos - lastX;
	float deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(deltaX, deltaY);
}
#pragma endregion

unsigned int loadImageToGUP(const char *fileName, GLint internalFormat, GLenum format, int textureSlot) {
	//��ͼƬ����Texture buffer���󶨵�TEXTURE_2D
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);		//bindǰҪ���ƶ���λ��ʹ�ò�ͬ��buffer������ռͬһ����λ��֮�����ͨ����λ����ҵ���Ҫ��Texture(����ע�⣬ʹ�õ���0�Ų�(TEXTURE0))
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	//ͨ��stb����ͼƬ
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);		//���ص�ͼƬy����������ͨ����opengl�෴����˿���ͨ����һ���ڼ���ͼƬʱ�Զ���תy����
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Load image failed.\n");
	}
	stbi_image_free(data);

	return TexBuffer;
}

int main(int argc, char *argv[]) {

	std::string exePath = argv[0];

#pragma region Open A Window
	//glfw����س�ʼ������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	//mac�ã�ǰ��������

	GLFWwindow *window = glfwCreateWindow(800, 600, "Lighting", nullptr, nullptr);	//���ڵ�col��row��title
	if (window == nullptr) {
		printf("Open GLFW window failed.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	//��Ϊ������
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//����ʾ���λ��
	glfwSetCursorPosCallback(window, mouse_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);		//���ƿɻ�������
	glEnable(GL_DEPTH_TEST);		//����ʹ��z-buffer���������Ϣ

	//���濪�����޳����ܣ����治�ᱻ����
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//����ģʽ��ֻ��������
#pragma endregion

#pragma region Init Shader
	//��ȡshader������
	Shader *myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	myShader->test();
#pragma endregion

#pragma region Init Material
	Material *myMaterial = new Material(
		myShader,
		glm::vec3(1.0f, 1.0f, 1.0f),
		loadImageToGUP("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
		loadImageToGUP("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
		128.0f
	);
#pragma endregion

#pragma region Init VAO��VBO��EBO and load data
	//Mesh cube(vertices);
	Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit.obj");	//�ļ�����ִ���ļ�ͬ��Ŀ¼��DebugĿ¼��

	////�������̣�bind VAO -> bind VBO -> copy vertices array in a buffer -> set vertex attributes pointers -> draw the object

	////��������VAO��Vertex Array Object������������󣬱��涥�����ݵĸ�ʽ�ͣ������VBO��������ã�
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);	//����1�����ص�VAO����������2����������VAO��ţ����ն��ʱ����2ӦΪ����
	//glBindVertexArray(VAO);

	////��������VBO��Vertex Buffer Objects�����㻺������Կ��洢�ռ��п��ٳ����ڴ滺�������洢�����������Ϣ���������ꡢ����������ɫ���ݵȣ�
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////���û����ݸ��Ƶ�Ŀǰ�󶨵�buffer�У�����1��buffer���ͣ�Array Buffer��������2�����ݳ��ȣ�����3���������飬����4��GPU�������ݵı��Ƶ�ʣ�����Ϊ��GL_STATIC_DRAW��GL_DYNAMIC_DRAW��GL_STREAM_DRAW
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////��������EBO�������������Element Buffer Object��EBO����ͨ���������VBO��ͬһ��������ظ�ʹ�ã�
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	////��һ���ǽ�VBO����VAO�е�attribute pointer����λ��
	////VBO֪ͨVAO����һ��0����λ������1��������ֵÿ3������һ�ݣ�����2����ÿ����ֵ����һ����������Ҫ��Ҫ��һ����-1~1��0~1����һ����������Ҫ������٣���һ����������Ҫƫ�ƶ���
	//glEnableVertexAttribArray(0);	//����0�Ų�λ
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	//glEnableVertexAttribArray(3);	//��Ϊ������䣬�̶�VAO��0�Ų۷�������Ϣ��1�Ų۷���ɫ��Ϣ��2�Ų۷�������Ϣ��3�ŷŷ�������Ϣ��
#pragma endregion

#pragma region More texture functions
	//����������������Ҫ���塣��������Ĭ��Ϊ0~1�������������Χʱ�������Ĳ��־�Ҫͨ��ĳ�ַ�����䣬���������Ϊ�����Ʒ�ʽ��
	//���Ʒ�ʽ�����������Զ�һ��������������ã���ͬ��������Խ��в�ͬ�����ã�
	//��Ĭ�ϣ�GL_REPEAT		�ظ�����ͼ��
	//GL_MIRRORED_REPEAT	��GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	//GL_CLAMP_TO_EDGE		��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	//GL_CLAMP_TO_BORDER	����������Ϊ�û�ָ���ı�Ե��ɫ��
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	//�ڶ�����������ΪS��T��R����������ά��
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);	//������������ΪGL_TEXTURE_BORDER_COLORʱ����Ҫͨ��һ��float����ָ����Ե��չ����ɫ

	//��һ�������ǹ��˷�ʽ����Ϊѡȡ������ֵ�����Ǻ�ϸ΢�ģ���0.0001�����������ֵ��С����Ҫ���Ƿ���ʲô��ɫֵ��
	//���˷�ʽ��Ҫ����GL_NEAREST���ٽ����ˣ�ѡȡ������������������ĵ㣬ֱ�ӻ������ɫֵ����GL_LINEAR����Bi��Linear�����Թ��ˣ���������ļ������ص���ɫֵ����һ�����Բ�ֵ��
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);			//�����ʾ��Сʱ�ٽ����ˣ��Ŵ�ʱ���Թ���

	//�༶��Զ����mipmap��TriLinear����Ҫ������С��ʱ��
	//��һ������������Ƿǳ�Զʱ����û��Ҫ�������̫������ȥ������ɫ����˿���Ԥ�ȼ���ö���ֱ��ʲ�ͬ��ͼ���������Һ�Զʱ�øĵͷֱ�����ͼ���Լ��ټ���
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	//��һ��LINEAR��ʾԶ���滻ʱ�����Բ�ֵ���в������ڶ��������ԭ���Ŀռ��ϵĹ��˷�ʽ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#pragma endregion

#pragma region Init and load textures
	//��ʵ�ϣ�TEXTURE_2D��������ۣ�����ͬʱ������texture buffer�����ݰ��ϣ���GPU��֮���shader�п��Զ�ȡ
	//unsigned int TexBufferA;
	//TexBufferA = loadImageToGUP("container.jpg", GL_RGB, GL_RGB, 0);
	//unsigned int TexBufferB;	//�ڶ���texture bufferҪ�ڵ�һ����ɰ󶨺���д���
	//TexBufferB = loadImageToGUP("awesomeface.png", GL_RGBA, GL_RGBA, 3);

#pragma endregion

#pragma region Prepare MVP matrices
	//calculate transformation matrix here��ͨ��uniform����vertex shader(����������ֱ�Ϊ�ҡ��ϡ���Ļ��)
	//opengl����������ϵ��Unity����������ϵ
	//�������˳������������ת��λ�ƣ���Ϊ�����λ�������ţ�λ����Ҳ�ᱻ����;ͬ������תҲ�����local space�������world space����������
	//����λ����������ģ���� V = t * r * s * V������˳�����λ�ơ���ת�����ţ�glm���߼����෴�ģ�
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-0.01f, 0.0f, 0.0f));	//����������λ��������������ݱ任����任���ٽ���λ�ƣ�-1~1��
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));	//�ڶ�����������ת�Ļ��ȣ�����������ת��
	//��ת���������泯�����ʱ����ʱ�뷽��
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));		//����ά�ȵķŴ����

	//����������ϵ�任��
	//������������ת�������꣬��Ц������
	glm::mat4 modelMat;
	//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//��������(0,0,3)����һ�����
	glm::mat4 viewMat;
	//viewMat = camera.GetViewMatrix();
	//ת�䵽��οռ䣬�Ž�Ϊ45�ȣ�perspective��800/600������͸�ӳ����Ͳü���
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion

	while (!glfwWindowShouldClose(window)) {
		//textureһ·������
		//trans = glm::translate(trans, glm::vec3(-0.01f, 0.0f, 0.0f));	//����������λ��������������ݱ任����任���ٽ���λ��
		//textureתȦ
		//trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));	//�ڶ�����������ת�Ļ��ȣ�����������ת��(������ԣ���ʱ��)
		//texture�Ŵ�
		//trans = glm::scale(trans, glm::vec3(1.01f, 1.01f, 1.01f));		//����ά�ȵķŴ����
		//��cpuʱ����Ϊ��ת�Ļ��Ȳ�������
		//glm::mat4 trans;
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					//����ΪRGB+��͸���ȣ���ΧΪ0-1
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//����Ⱦ��һ֡ǰ��ǰһ֡����ɫ��Ϣ��z-buffer�������Ϣ�����

		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 1; i++) {
			// Set Model Matrixes
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);	//����1�ǵ�λ����

			// Set View and Projection Matrices if you want.

			// Set Material -> Shader Program
			myShader->use();
			//// Set Material -> Textures
			//glActiveTexture(GL_TEXTURE0);		//������λ������
			//glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			//glActiveTexture(GL_TEXTURE0 + 1);
			//glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
			// Set Material -> Uniform
			//��shader�����е�һ��uniform���һ������ֵ������Ϊ��myShader->ID��shader�����е�ourTexture���uniform������ȡ��texture����0�Ų۰�
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
			//ͨ��uniform����任����
			//��������任��uniform
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

#pragma region Load Lights
			//����ɺ������ɫ�Ĺ�Դ
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.3f, 0.3f, 0.3f);	//������

			//���²��������һ��ƽ�й�Դ���ĸ����Դ��һ���۹�Դ
			
			//ƽ�й�Դ����Uniform����
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.pos"), light.position.x, light.position.y, light.position.z);		//��Դλ�ã����Դ��Ҫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), light.color.x, light.color.y, light.color.z);				//��Դ��ɫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), light.direction.x, light.direction.y, light.direction.z);	//��Դ����
			
			//���Դ����Uniform����
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);		//��Դλ�ã����Դ��Ҫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);				//��Դ��ɫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);	//��Դ����
			//���Դ˥��ϵ��
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			//���Դ����Uniform����
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);		//��Դλ�ã����Դ��Ҫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);				//��Դ��ɫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);	//��Դ����
			//���Դ˥��ϵ��
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

			//���Դ����Uniform����
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);		//��Դλ�ã����Դ��Ҫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);				//��Դ��ɫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);	//��Դ����
			//���Դ˥��ϵ��
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

			//���Դ����Uniform����
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);		//��Դλ�ã����Դ��Ҫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);				//��Դ��ɫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);	//��Դ����
			//���Դ˥��ϵ��
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);

			//�۹�Դ����Uniform����
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);		//��Դλ�ã����Դ��Ҫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);				//��Դ��ɫ
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);	//��Դ����
			//���Դ˥��ϵ��
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
			//�۹�Դ����Ƕ�
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOuter"), lightS.cosPhyOuter);
#pragma endregion

#pragma region Load material
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			//������
			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
#pragma endregion

			//// Set Model
			//glBindVertexArray(VAO);

			//// Drawcall
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			
			//cube.Draw(myMaterial->shader);
			//model.Draw(myMaterial->shader);
		}
		//cube.Draw(myMaterial->shader);
		model.Draw(myMaterial->shader);

		glfwSwapBuffers(window);		//����������ɫ�ݴ����飨ÿ�����ض�����������ɫ�ݴ����飩
		//��ֻ������bufferд��ʱ��ͼ�������ܻ���˸��Ϊ�˿˷����⣬����ʹ��˫bufferȥ��Ⱦ��
		glfwPollEvents();				//��ȡ�û��İ�����������
		//������������Զ��崦�����Ǵ���ģ�Ӧ����������ӣ�����һ��ѭ���Ŀ�ͷ������һ��ѭ���л�õ�������������ӳٵ��µĴ���

		camera.UpdateCameraPosition();	//ͨ������W��S���ƶ������ͨ��������Ⱦѭ�����������һ��ѭ���д���
	}
	glfwTerminate();		//�뿪ʱ��Ҫ����ɾ�������õ���Դ
	return 0;
}
