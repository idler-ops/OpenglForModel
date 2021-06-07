//GPUʹ��shaderʱ���˴�VAO��������ֱ�Ӵ�CPUͨ��uniform��ò�����������opengl��cpu������Ҫ�����Ӧ����
//fragmentShaderҪ�����ɫ���������Լ�������
//ע����������*�ĵĶ����Ǹ������ֱ����

#version 330 core
struct Material {
	vec3 ambient;
//	vec3 diffuse;
	sampler2D diffuse;
//	vec3 specular;
	sampler2D specular;
	float shininess;
};

struct LightDirectional {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
	float cosPhyInner;
	float cosPhyOuter;
};

uniform LightDirectional lightD;	//ƽ�й�Դ

uniform LightPoint lightP0;		//�������Դ˥��
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;

uniform LightSpot lightS;		//�۹�Դ����Ҫ�����ж��Ƿ������䷶Χ��

uniform Material material;		//���տ��Ե�����ɫֵ

//in vec4 vertexColor;
in vec2 TexCoord;		//��Ӧ��ͼ�е�uv����
in vec3 FragPos;		//��ǰ������
in vec3 Normal;			//������

//uniform sampler2D ourTexture;	//2D��ͼ
//uniform sampler2D ourFace;

uniform vec3 objColor;
//Phong Model��������ǿ�ȷ�Ϊambient�������⣬�뵥��ι�����Ĺ�Դ�޹أ���diffuse�������䣩��Specular��������գ���ע��ÿ�����ֵ���Сֵ��Ϊ0���������ձ��˵Ĺ���ǿ�ȣ�
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

//uniform vec4 ourColor;

out vec4 FragColor;

//��װƽ�й�Դ
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera) {
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(light.dirToLight, uNormal), 0);
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-light.dirToLight, uNormal));	// ��������������Ϊ����������������
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//��װ���Դ
vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//����ǹ����յ��õ�ķ���ĵ�λ����
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//���Դʵ�ʹ���˥��
	
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// ��������������Ϊ����������������
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//��װ�۹�Դ
vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//����ǹ����յ��õ�ķ���ĵ�λ����
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//���Դʵ�ʹ���˥��
	float spotRatio = 0;
	float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);		//��Դ����ķ����� ��� ��Դ����Ƭ�εķ���
	
	//cosTheta > light.cosPhyInner��cosTheta < light.cosPhyOuter
	spotRatio = (light.cosPhyOuter - cosTheta) / (light.cosPhyOuter - light.cosPhyInner);	
	spotRatio = max(0.0f, min(1.0f, spotRatio));	//���ñ�Ե����

	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation * spotRatio;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// ��������������Ϊ����������������
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation * spotRatio;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

void main() {
	vec3 finalResult = vec3(0.0f, 0.0f, 0.0f);
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);		//�Ӹõ㵽���������
//	vec3 ambient = texture(material.diffuse, TexCoord).rgb * material.ambient * ambientColor;	//Ϊ������Ӱ��Ҳ��������������ҲҪ��������

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);
	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0f);
//	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);


//	float dist = length(lightPos - FragPos);
//	float attenuation = 1.0 / (lightP.constant + lightP.linear * dist + lightP.quadratic * (dist * dist));	//���Դʵ�ʹ�����
//
//	vec3 lightDir = normalize(lightPos - FragPos);	//����ǹ����յ��õ�ķ���ĵ�λ����
//	vec3 reflectVec = reflect(-lightDir, Normal);	//���㷴������������Ϊ����������������
//	vec3 cameraVec = normalize(cameraPos - FragPos);	//�Ӹõ㵽���������
//
//	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
//	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor;
////	vec3 specular = material.specular * specularAmount * lightColor;		//���淴��ľ�������������Լ�����ʵ���������ͬ���������ݾ���ȡ���
//	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;	//�����
////	vec3 diffuse = texture(material.diffuse, TexCoord).rgb;		//������ͼ��uv����
//
////	vec3 ambient = material.ambient * ambientColor;
//	vec3 ambient = texture(material.diffuse, TexCoord).rgb * material.ambient * ambientColor;	//Ϊ������Ӱ��Ҳ��������������ҲҪ��������
//
//	float cosTheta = dot(normalize(FragPos - lightPos), -1 * lightDirUniform);
//
//	float spotRatio = (lightS.cosPhyOuter - cosTheta) / (lightS.cosPhyOuter - lightS.cosPhyInner);;
//	
//	spotRatio = max(0.0f, min(1.0f, spotRatio));	//���ñ�Ե����
////	if (cosTheta > lightS.cosPhyInner) {
////		//inside
////		spotRatio = 1.0f;
////	} else if (cosTheta > lightS.cosPhyOuter) {
////		//middle
////		spotRatio = (lightS.cosPhyOuter - cosTheta) / (lightS.cosPhyOuter - lightS.cosPhyInner);
////	} else {
////		//outer	
////		spotRatio = 0.0f;
////	}
//
//	FragColor = vec4((ambient + (diffuse + specular) * spotRatio) * objColor, 1.0f);
////	FragColor = vec4((ambient + (diffuse + specular) * attenuation) * objColor, 1.0f);
////	FragColor = vec4((diffuse + ambientColor) * objColor, 1.0f);
////	FragColor = vec4(objColor * ambientColor, 1.0f);
////	FragColor = vec4(objColor * ambientColor, 1.0f) * texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);	//���texture��һ������
//
////mix������Ҫ��������ֵ��Ϊ�������������Ǹ��ݵ����������������Բ�ֵ��
////0.2����᷵��80%�ĵ�һ��������ɫ��20%�ĵڶ���������ɫ����������������Ļ��ɫ��
////	FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2) * vertexColor;
////	FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2);
////	FragColor = texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);		//����Ϊ���� ����1 �ز��е� ����2 ����ȡ��ɫ��������Ⱦ��Ӧ�ĵ㣬��������,�����ǻ�������ͼ���غ�
}
