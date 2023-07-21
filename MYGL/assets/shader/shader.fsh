#version 330 core

//材质
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

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

	FragColor = vec4(result, 1.0f);
}