/**
物体的颜色定义为：它从光源反射的每种颜色成分的数量
Color vector：通过红色、绿色和蓝色分量的组合描绘大多数现实世界颜色的矢量（缩写为RGB）。物体的颜色是物体没有吸收的反射颜色成分。
Phong lighting model：通过计算环境光、漫反射和镜面反射分量来近似真实世界照明的模型。
Ambient lighting：通过为每个对象提供较小的亮度来近似全局照明，以便对象在不直接照明的情况下不会完全黑暗。
Diffuse shading：顶点/片段与光源对齐得越多，光照就越强。利用法线向量来计算角度。
Normal vector：垂直于表面的单位向量。
Normal matrix：3x3 矩阵，即未经平移的模型（或模型视图）矩阵。它还以这样的方式（逆转置）进行修改，以便在应用非均匀缩放时保持法线向量面向正确的方向。
否则，当使用非均匀缩放时，法向量会失真。
Specular lighting：根据观察者的方向、反射光线的方向和设置高光散射量的光泽度值。角度越小越亮。
*/

#version 330 core

//材质
//物体反射的环境色、漫反射色和镜面色。这些设置了对象的颜色。
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

//Light (properties)：光的环境强度、漫反射强度和镜面反射强度。它们可以采用任何颜色值，并定义光源为每个特定 Phong 组件发出的颜色/强度
//方向光源
struct DirLight {
	vec3 direction;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight; 

//点光源
struct PointLight {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 10
uniform int pointLightNum;
uniform PointLight pointLights[NR_POINT_LIGHTS]; 

//聚光灯
struct SpotLight {
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotLight; 

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float intensity;

// texture sampler
uniform sampler2D texture1;

//相机位置（眼睛位置）
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	vec3 reflectDir = reflect(-lightDir, normal); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	//根据距离衰减
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 lightDir = normalize(light.position - FragPos);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	vec3 reflectDir = reflect(-lightDir, normal); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	ambient *= attenuation; 
	diffuse *= attenuation;
	specular *= attenuation; 

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	//根据距离衰减
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//光照射到片段的方向向量
	vec3 lightDir = normalize(light.position - FragPos);
	//聚光灯的方向
	vec3 spotDir = normalize(-light.direction);
	//求它们的余弦值
	float theta = dot(lightDir, spotDir);
	float epsilon = (light.cutOff - light.outerCutOff);
	//边缘模糊处理
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) * intensity;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.diffuse, TexCoord)) * intensity;

	ambient *= attenuation; 
	diffuse *= attenuation;
	specular *= attenuation; 

	return (ambient + diffuse + specular);
}

void main()
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), intensity) * vec4(ourColor, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2) * vec4(ourColor, 1.0f);
	// FragColor = texture(texture2, TexCoord);
	// FragColor = texture(texture1, TexCoord);
	// FragColor = vec4(ourColor, 1.0f);

	//specular(高光反射)，反射出来的是光源的颜色

	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = CalcDirLight(dirLight, normal, viewDir);

	for(int i = 0; i < pointLightNum; i++) {
		result += CalcPointLight(pointLights[i], normal, viewDir);
	}

	result += CalcSpotLight(spotLight, normal, viewDir);

	// vec3 result = dirLight.ambient *  ourColor;

	FragColor = vec4(result, 1.0f);
}