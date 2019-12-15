#version 330 core

in vec3 normal;
in vec3 fragPosition;

uniform float ambientIntensity;
uniform vec3 lightColor;
uniform vec3 lightPosition;

out vec4 fragmentColor;

void main()
{
	// Ambient light
	vec3 ambient = ambientIntensity * lightColor;

	// Diffuse light
	vec3 normalDirection = normalize(normal);
	vec3 fragToLightDirection = normalize(lightPosition - fragPosition);
	float diffuseIntensity = max(dot(normalDirection, fragToLightDirection), 0.0f);
	vec3 diffuse = diffuseIntensity * lightColor;

	vec3 result = ambient + diffuse;
	fragmentColor = vec4(result, 1.0f);
}