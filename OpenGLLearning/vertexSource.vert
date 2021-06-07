//GLSL的shader源代码
//从0号（0~15，具体范围和使用的显卡有关）attribute取数据到vec3 （名称）aPos作为shader的input
//改变片段着色器的数量（？）
//#version 330 core 表示应用于openGL3.3.0
//layout(location = 0)表示从0号VAO槽取出，in表示输入该shader，out表示从该shader输出，vec3表示3维向量，vec4表示4维向量（还有bvec、ivec、uvec、dvec），aPos为变量名
//vertexShader固定输出gl_Position（不用定义），fragmentShader可以输出FragColor来控制颜色

#version 330 core
layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;							//vertices中添加了颜色信息
layout(location = 2) in vec2 aTexCoord;							//再添加2维的纹理信息，表示顶点对应的纹理中点的坐标
layout(location = 3) in vec3 aNormal;							//输入法向量

//uniform mat4 transform;							//送进来的变换矩阵
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;
out vec2 TexCoord;

//线段中插入点的Position和经过变换的法向量
out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;		//之前没有这个，相当于只有光源坐标没有被照射点坐标，所有地方得到的都是平行光
//	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);		//乘上变换矩阵进行变换

//	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
	TexCoord = aTexCoord;

//	Normal = mat3(modelMat) * aNormal;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;	//做这样的额外操作是为了避免长宽比改变导致法向量不再是法向量的情况
}
