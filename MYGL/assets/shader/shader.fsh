#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float intensity;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), intensity) * vec4(ourColor, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2) * vec4(ourColor, 1.0f);
	// FragColor = texture(texture2, TexCoord);
	// FragColor = texture(texture1, TexCoord);
	// FragColor = vec4(ourColor, 1.0f);


	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), intensity) * vec4(ambient + diffuse + specular, 1.0f);
	// FragColor = vec4(1.0f,0.5f,0.31f, 1.0f)  * vec4(ambient + diffuse + specular, 1.0f);
}