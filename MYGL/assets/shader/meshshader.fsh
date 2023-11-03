/**
物体的颜色定义为：未被物体吸收（拒绝）的颜色就是我们感知到的颜色。它仅反映那些代表物体颜色的颜色，而这些颜色的组合就是我们所感知的.
Ex：
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);反射1.0的红色光，0.5的绿色光，0.31的蓝色光
glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);
我们可以看到，toy的颜色吸收了大部分白光，但根据自身的颜色值反射了几个红、绿、蓝值。这是颜色在现实生活中如何发挥作用的表示。
因此，我们可以将物体的颜色定义为它从光源反射的每种颜色成分的数量。
*/

/**
环境照明：即使在黑暗的时候，世界上的某个地方通常仍然有一些光（月亮，远处的光），所以物体几乎永远不会完全黑暗。
为了模拟这一点，我们使用环境照明常量，该常量总是为对象提供一些颜色。
漫射照明：模拟光对象对对象的定向影响。 这是照明模型中视觉上最重要的组成部分。 物体的一部分越靠近光源，它就越亮。
镜面照明：模拟出现在闪亮物体上的光亮点。镜面高光更倾向于光的颜色而不是物体的颜色。
*/

/**
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
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
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

in vec2 TexCoord;

//物体的旋转、缩放会影响法向量，所以这里是一个正规矩阵处理之后的向量，在vs着色器中处理
in vec3 Normal;

in vec3 FragPos;

uniform float intensity;

// texture sampler
uniform sampler2D texture1;

//相机位置（眼睛位置）
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	//环境照明
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));

	//（0-90度）对应的余弦值（1-0）
	//漫反射(点乘求余弦值，光照射的向量和法线向量的夹角越小，则漫反射效果越强)
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));

	//高光
	vec3 reflectDir = reflect(-lightDir, normal); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	//根据距离衰减
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//光照射的向量
	vec3 lightDir = normalize(light.position - FragPos);

	//环境照明
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));

	//（0-90度）对应的余弦值（1-0）
	//漫反射(点乘求余弦值，光照射的向量和法线向量的夹角越小，则漫反射效果越强)
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));

	//高光
	vec3 reflectDir = reflect(-lightDir, normal); 	//求光线从物体表面反射出去的向量
	//反射光线和眼睛的夹角（角度越小效果越强）
	//shininess光泽度亮点的价值
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));

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

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));

	//漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord)) * intensity;

	//高光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_diffuse1, TexCoord)) * intensity;

	ambient *= attenuation; 
	diffuse *= attenuation;
	specular *= attenuation; 

	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = CalcDirLight(dirLight, normal, viewDir);

	for(int i = 0; i < pointLightNum; i++) {
		result += CalcPointLight(pointLights[i], normal, viewDir);
	}

	result += CalcSpotLight(spotLight, normal, viewDir);

	FragColor = vec4(result, 1.0f);

	// FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}