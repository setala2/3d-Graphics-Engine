#version 330 core

out vec4 color;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;

uniform vec3 lightPosition;
uniform sampler2D theTexture;

void main()
{
	float ambientIntensity = 0.2f;
	vec4 ambient = texture(theTexture, TexCoords) * ambientIntensity;
	
	vec3 unitNormal = normalize(Normal);
	vec3 fragToLight = normalize(lightPosition - FragPosition);
	float diffuseIntensity = max(dot(unitNormal, fragToLight), 0.0f);
	vec4 diffuse = texture(theTexture, TexCoords) * diffuseIntensity;

	color = ambient + diffuse;
}
