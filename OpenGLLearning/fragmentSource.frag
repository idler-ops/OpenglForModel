//GPU使用shader时除了从VAO，还可以直接从CPU通过uniform获得参数，不过在opengl的cpu程序中要添加相应处理
//fragmentShader要输出颜色参数（可自己命名）
//注意这里向量*的的定义是各分量分别相乘

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

uniform LightDirectional lightD;	//平行光源

uniform LightPoint lightP0;		//调整点光源衰减
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;

uniform LightSpot lightS;		//聚光源，主要用来判断是否在照射范围内

uniform Material material;		//最终可以调整颜色值

//in vec4 vertexColor;
in vec2 TexCoord;		//对应贴图中的uv坐标
in vec3 FragPos;		//当前点坐标
in vec3 Normal;			//法向量

//uniform sampler2D ourTexture;	//2D贴图
//uniform sampler2D ourFace;

uniform vec3 objColor;
//Phong Model：将光照强度分为ambient（环境光，与单独喂进来的光源无关）、diffuse（漫反射）、Specular（镜面光照），注意每个部分的最小值都为0（不能吸收别人的光照强度）
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

//uniform vec4 ourColor;

out vec4 FragColor;

//封装平行光源
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera) {
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(light.dirToLight, uNormal), 0);
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-light.dirToLight, uNormal));	// 反射向量，参数为入射向量、法向量
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//封装点光源
vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//这个是光线照到该点的方向的单位向量
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//点光源实际光照衰减
	
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// 反射向量，参数为入射向量、法向量
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//封装聚光源
vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//这个是光线照到该点的方向的单位向量
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//点光源实际光照衰减
	float spotRatio = 0;
	float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);		//光源方向的反方向 点乘 光源到该片段的方向
	
	//cosTheta > light.cosPhyInner、cosTheta < light.cosPhyOuter
	spotRatio = (light.cosPhyOuter - cosTheta) / (light.cosPhyOuter - light.cosPhyInner);	
	spotRatio = max(0.0f, min(1.0f, spotRatio));	//设置边缘渐变

	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation * spotRatio;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// 反射向量，参数为入射向量、法向量
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation * spotRatio;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

void main() {
	vec3 finalResult = vec3(0.0f, 0.0f, 0.0f);
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);		//从该点到相机的向量
//	vec3 ambient = texture(material.diffuse, TexCoord).rgb * material.ambient * ambientColor;	//为了让阴影面也具有纹理，环境光也要乘上纹理

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);
	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0f);
//	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);


//	float dist = length(lightPos - FragPos);
//	float attenuation = 1.0 / (lightP.constant + lightP.linear * dist + lightP.quadratic * (dist * dist));	//点光源实际光照量
//
//	vec3 lightDir = normalize(lightPos - FragPos);	//这个是光线照到该点的方向的单位向量
//	vec3 reflectVec = reflect(-lightDir, Normal);	//计算反射向量，参数为入射向量、法向量
//	vec3 cameraVec = normalize(cameraPos - FragPos);	//从该点到相机的向量
//
//	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess);
//	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor;
////	vec3 specular = material.specular * specularAmount * lightColor;		//镜面反射的具体规则依材料以及表面实际情况而不同，这里依据经验取点乘
//	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;	//做点乘
////	vec3 diffuse = texture(material.diffuse, TexCoord).rgb;		//哪张贴图的uv坐标
//
////	vec3 ambient = material.ambient * ambientColor;
//	vec3 ambient = texture(material.diffuse, TexCoord).rgb * material.ambient * ambientColor;	//为了让阴影面也具有纹理，环境光也要乘上纹理
//
//	float cosTheta = dot(normalize(FragPos - lightPos), -1 * lightDirUniform);
//
//	float spotRatio = (lightS.cosPhyOuter - cosTheta) / (lightS.cosPhyOuter - lightS.cosPhyInner);;
//	
//	spotRatio = max(0.0f, min(1.0f, spotRatio));	//设置边缘渐变
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
////	FragColor = vec4(objColor * ambientColor, 1.0f) * texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);	//结合texture用一下试试
//
////mix函数需要接受两个值作为参数，并对它们根据第三个参数进行线性插值。
////0.2代表会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
////	FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2) * vertexColor;
////	FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2);
////	FragColor = texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);		//函数为：从 参数1 素材中的 参数2 坐标取颜色返还并渲染对应的点，画出箱子,这里是画出两张图的重合
}
