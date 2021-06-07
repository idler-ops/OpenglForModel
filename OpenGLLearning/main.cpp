//首先靠自己直接复原一下画出箱子的过程

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
//10个立方体距离原立方体的位移距离。这里只改变position
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

//下面的用于EBO，暂时不用
unsigned int indices[] =
{
	0, 1, 2,
	2, 3, 0
};
#pragma endregion

#pragma region Camera Declare
//初始化相机对象
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
#pragma endregion

#pragma region Light Declare
LightDirectional light(
	glm::vec3(1.0f, 1.0f, -1.0f), 
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f), 
	glm::vec3(1.0f, 1.0f, 1.0f));

LightPoint lightP0(
	glm::vec3(1.0f, 0.0f, 0.0f),								//坐标 
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),	//角度
	glm::vec3(1.0f, 0.0f, 0.0f));								//颜色
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
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f),		//这个方向是向下
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion

#pragma region Input Declare
bool firstMouse = true;		//用于mouse callback
float lastX, lastY;			//记录mouse位置变化

void processInput(GLFWwindow *window) {		//记录发生的按键事件，以便后续处理
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

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	//下沉
		camera.speedY = -10.0f;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.speedY = 10.0f;
	else
		camera.speedY = 0.0f;
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {		//捕捉鼠标移动
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
	//将图片读入Texture buffer并绑定到TEXTURE_2D
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);		//bind前要先移动槽位，使得不同的buffer不会抢占同一个槽位，之后可以通过槽位序号找到想要的Texture(这里注意，使用的是0号槽(TEXTURE0))
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	//通过stb加载图片
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);		//加载的图片y轴正负方向通常与opengl相反，因此可以通过这一步在加载图片时自动反转y坐标
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
	//glfw库相关初始化配置
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	//mac用，前向相容性

	GLFWwindow *window = glfwCreateWindow(800, 600, "Lighting", nullptr, nullptr);	//窗口的col、row、title
	if (window == nullptr) {
		printf("Open GLFW window failed.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	//设为主窗口
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//不显示鼠标位置
	glfwSetCursorPosCallback(window, mouse_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);		//控制可绘制区域
	glEnable(GL_DEPTH_TEST);		//开启使用z-buffer保存深度信息

	//下面开启面剔除功能，背面不会被画出
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//框线模式，只画出框线
#pragma endregion

#pragma region Init Shader
	//读取shader程序码
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

#pragma region Init VAO，VBO，EBO and load data
	//Mesh cube(vertices);
	Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit.obj");	//文件放在执行文件同级目录的Debug目录下

	////下面流程：bind VAO -> bind VBO -> copy vertices array in a buffer -> set vertex attributes pointers -> draw the object

	////创建并绑定VAO（Vertex Array Object，顶点数组对象，保存顶点数据的格式和（多个）VBO对象的引用）
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);	//参数1：返回的VAO个数，参数2：用来接收VAO序号，接收多个时参数2应为数组
	//glBindVertexArray(VAO);

	////创建并绑定VBO（Vertex Buffer Objects，顶点缓冲对象，显卡存储空间中开辟出的内存缓存区，存储顶点的属性信息，包括坐标、法向量、颜色数据等）
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////将用户数据复制到目前绑定的buffer中，参数1：buffer类型（Array Buffer），参数2：数据长度，参数3：数据数组，参数4：GPU处理数据的变更频率，可以为：GL_STATIC_DRAW、GL_DYNAMIC_DRAW、GL_STREAM_DRAW
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////创建并绑定EBO（索引缓冲对象（Element Buffer Object，EBO），通过索引解决VBO中同一个顶点的重复使用）
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	////这一步是将VBO放入VAO中的attribute pointer（槽位）
	////VBO通知VAO开启一个0号栏位（参数1），将数值每3个当成一份（参数2），每个数值都是一个浮点数，要不要归一化到-1~1或0~1，下一个顶点资料要间隔多少，第一个顶点资料要偏移多少
	//glEnableVertexAttribArray(0);	//激活0号槽位
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	//glEnableVertexAttribArray(3);	//（为方便记忆，固定VAO的0号槽放坐标信息，1号槽放颜色信息，2号槽放纹理信息，3号放法向量信息）
#pragma endregion

#pragma region More texture functions
	//纹理有两个特性需要定义。纹理坐标默认为0~1，当超过这个范围时，超出的部分就要通过某种方法填充，这个方法称为“环绕方式”
	//环绕方式包括：（可以对一个轴向方向进行设置，不同轴向方向可以进行不同的设置）
	//（默认）GL_REPEAT		重复纹理图像。
	//GL_MIRRORED_REPEAT	和GL_REPEAT一样，但每次重复图片是镜像放置的。
	//GL_CLAMP_TO_EDGE		纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	//GL_CLAMP_TO_BORDER	超出的坐标为用户指定的边缘颜色。
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	//第二个参数可以为S、T、R，代表三个维度
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);	//当第三个参数为GL_TEXTURE_BORDER_COLOR时，需要通过一个float数组指定边缘拓展的颜色

	//另一个特性是过滤方式。因为选取的坐标值允许是很细微的（如0.0001），如果像素值较小则需要考虑返回什么颜色值。
	//过滤方式主要包括GL_NEAREST（临近过滤，选取离坐标最近的像素中心点，直接获得其颜色值）、GL_LINEAR（（Bi）Linear，线性过滤，基于最近的几个像素的颜色值计算一个线性插值）
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);			//这里表示缩小时临近过滤，放大时线性过滤

	//多级渐远纹理（mipmap，TriLinear）主要用在缩小的时候
	//当一个物体距离我们非常远时，就没必要对其进行太多运算去计算颜色，因此可以预先计算好多个分辨率不同的图，当距离我很远时用改低分辨率贴图，以减少计算
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	//第一个LINEAR表示远近替换时用线性插值进行采样，第二个则就是原来的空间上的过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#pragma endregion

#pragma region Init and load textures
	//事实上，TEXTURE_2D包括多个槽，可以同时将几个texture buffer的内容绑定上，让GPU在之后的shader中可以读取
	//unsigned int TexBufferA;
	//TexBufferA = loadImageToGUP("container.jpg", GL_RGB, GL_RGB, 0);
	//unsigned int TexBufferB;	//第二个texture buffer要在第一个完成绑定后进行处理
	//TexBufferB = loadImageToGUP("awesomeface.png", GL_RGBA, GL_RGBA, 3);

#pragma endregion

#pragma region Prepare MVP matrices
	//calculate transformation matrix here，通过uniform传给vertex shader(三轴正方向分别为右、上、屏幕外)
	//opengl是右手坐标系，Unity是左手坐标系
	//建议操作顺序：先缩放再旋转再位移，因为如果先位移再缩放，位移量也会被缩放;同样，旋转也会出现local space操作变成world space操作的问题
	//顶点位置是列主序的，因此 V = t * r * s * V，呼叫顺序就是位移、旋转、缩放（glm与逻辑是相反的）
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-0.01f, 0.0f, 0.0f));	//参数：矩阵、位移向量，代表根据变换矩阵变换后再进行位移（-1~1）
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));	//第二个参数是旋转的弧度，第三个是旋转轴
	//旋转方向是正面朝向该轴时的逆时针方向
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));		//三个维度的放大比例

	//下面是坐标系变换。
	//首先区域坐标转世界坐标，让笑脸倒下
	glm::mat4 modelMat;
	//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//接下来在(0,0,3)处架一个相机
	glm::mat4 viewMat;
	//viewMat = camera.GetViewMatrix();
	//转变到齐次空间，张角为45度，perspective是800/600（包含透视除法和裁剪）
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion

	while (!glfwWindowShouldClose(window)) {
		//texture一路往左跑
		//trans = glm::translate(trans, glm::vec3(-0.01f, 0.0f, 0.0f));	//参数：矩阵、位移向量，代表根据变换矩阵变换后再进行位移
		//texture转圈
		//trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));	//第二个参数是旋转的弧度，第三个是旋转轴(正向面对，逆时针)
		//texture放大
		//trans = glm::scale(trans, glm::vec3(1.01f, 1.01f, 1.01f));		//三个维度的放大比例
		//把cpu时间作为旋转的弧度参数传入
		//glm::mat4 trans;
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					//参数为RGB+不透明度，范围为0-1
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//在渲染下一帧前将前一帧的颜色信息和z-buffer（深度信息）清空

		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 1; i++) {
			// Set Model Matrixes
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);	//参数1是单位矩阵

			// Set View and Projection Matrices if you want.

			// Set Material -> Shader Program
			myShader->use();
			//// Set Material -> Textures
			//glActiveTexture(GL_TEXTURE0);		//启动槽位，读入
			//glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			//glActiveTexture(GL_TEXTURE0 + 1);
			//glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
			// Set Material -> Uniform
			//向shader程序中的一个uniform填充一个整数值，这里为将myShader->ID的shader程序中的ourTexture这个uniform（用来取得texture）与0号槽绑定
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
			//通过uniform传入变换矩阵
			//传入坐标变换的uniform
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

#pragma region Load Lights
			//传入珊瑚红颜色的光源
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.3f, 0.3f, 0.3f);	//环境光

			//以下部分添加了一个平行光源、四个点光源、一个聚光源
			
			//平行光源所需Uniform参数
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.pos"), light.position.x, light.position.y, light.position.z);		//光源位置，点光源需要
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), light.color.x, light.color.y, light.color.z);				//光源颜色
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), light.direction.x, light.direction.y, light.direction.z);	//光源方向
			
			//点光源所需Uniform参数
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);		//光源位置，点光源需要
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);				//光源颜色
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);	//光源方向
			//点光源衰减系数
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			//点光源所需Uniform参数
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);		//光源位置，点光源需要
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);				//光源颜色
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);	//光源方向
			//点光源衰减系数
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

			//点光源所需Uniform参数
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);		//光源位置，点光源需要
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);				//光源颜色
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);	//光源方向
			//点光源衰减系数
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

			//点光源所需Uniform参数
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);		//光源位置，点光源需要
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);				//光源颜色
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);	//光源方向
			//点光源衰减系数
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);

			//聚光源所需Uniform参数
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);		//光源位置，点光源需要
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);				//光源颜色
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);	//光源方向
			//点光源衰减系数
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
			//聚光源照射角度
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOuter"), lightS.cosPhyOuter);
#pragma endregion

#pragma region Load material
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			//材质球
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

		glfwSwapBuffers(window);		//交换两个颜色暂存区块（每个像素都存在两个颜色暂存区块）
		//当只往单个buffer写入时，图像结果可能会闪烁。为了克服问题，轮流使用双buffer去渲染。
		glfwPollEvents();				//获取用户的按键（操作）
		//在这下面添加自定义处理方法是错误的，应当在上面添加，在下一次循环的开头处理上一次循环中获得的命令，尽量避免延迟导致的错误

		camera.UpdateCameraPosition();	//通过按下W、S键移动相机（通常放在渲染循环的最后，在下一次循环中处理）
	}
	glfwTerminate();		//离开时不要忘记删除所配置的资源
	return 0;
}
