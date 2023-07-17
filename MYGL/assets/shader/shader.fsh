#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float intensity;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), intensity) * vec4(ourColor, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2) * vec4(ourColor, 1.0f);
	// FragColor = texture(texture2, TexCoord);
	// FragColor = texture(texture1, TexCoord);
	// FragColor = vec4(ourColor, 1.0f);
}