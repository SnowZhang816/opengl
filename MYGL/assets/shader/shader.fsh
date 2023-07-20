#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
    vec3 position;

	vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float intensity;

// texture sampler
uniform sampler2D texture1;
uniform vec3 viewPos;
uniform Material material;
uniform Light light; 

void main()
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), intensity) * vec4(ourColor, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2) * vec4(ourColor, 1.0f);
	// FragColor = texture(texture2, TexCoord);
	// FragColor = texture(texture1, TexCoord);
	// FragColor = vec4(ourColor, 1.0f);

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
    		    light.quadratic * (distance * distance));    

    // vec3 ambient = light.ambient * material.ambient;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	vec3 lightDir = normalize(light.position - FragPos);
	// vec3 lightDir = normalize(-light.direction);
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	// vec3 diffuse = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	// ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation; 

	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), intensity) * vec4(ambient + diffuse + specular, 1.0f);
	// vec3 t = vec3(texture(texture1, TexCoord));
	FragColor = vec4(1.0f,1.0f,1.0f, 1.0f)  * vec4(ambient + diffuse + specular, 1.0f);
}