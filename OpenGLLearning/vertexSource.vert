//GLSL��shaderԴ����
//��0�ţ�0~15�����巶Χ��ʹ�õ��Կ��йأ�attributeȡ���ݵ�vec3 �����ƣ�aPos��Ϊshader��input
//�ı�Ƭ����ɫ��������������
//#version 330 core ��ʾӦ����openGL3.3.0
//layout(location = 0)��ʾ��0��VAO��ȡ����in��ʾ�����shader��out��ʾ�Ӹ�shader�����vec3��ʾ3ά������vec4��ʾ4ά����������bvec��ivec��uvec��dvec����aPosΪ������
//vertexShader�̶����gl_Position�����ö��壩��fragmentShader�������FragColor��������ɫ

#version 330 core
layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;							//vertices���������ɫ��Ϣ
layout(location = 2) in vec2 aTexCoord;							//�����2ά��������Ϣ����ʾ�����Ӧ�������е������
layout(location = 3) in vec3 aNormal;							//���뷨����

//uniform mat4 transform;							//�ͽ����ı任����
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;
out vec2 TexCoord;

//�߶��в�����Position�;����任�ķ�����
out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;		//֮ǰû��������൱��ֻ�й�Դ����û�б���������꣬���еط��õ��Ķ���ƽ�й�
//	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);		//���ϱ任������б任

//	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
	TexCoord = aTexCoord;

//	Normal = mat3(modelMat) * aNormal;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;	//�������Ķ��������Ϊ�˱��ⳤ��ȸı䵼�·����������Ƿ����������
}
