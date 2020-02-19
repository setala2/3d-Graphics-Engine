#version 330 core

in vec3 fragPosition;
in vec3 normal;

out vec4 color;

uniform vec3 lightPosition;
uniform vec3 materialColor;

void main()
{
	float ambientIntensity = 0.2f;
	vec3 ambient = materialColor * ambientIntensity;

	vec3 unitNormal = normalize(normal);
	vec3 fragToLight = normalize(lightPosition - fragPosition);
	float diffuseIntensity = max(dot(unitNormal, fragToLight), 0.0f);
	vec3 diffuse = materialColor * diffuseIntensity;

	color = vec4(ambient + diffuse, 1.0f);
}
