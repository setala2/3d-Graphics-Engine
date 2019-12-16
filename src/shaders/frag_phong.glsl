#version 330 core

in vec3 normal;
in vec3 fragPosition;

uniform float ambientIntensity;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float specularIntensity;
uniform vec3 viewPosition;
uniform int shineExponent;

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

	// Specular
	vec3 fragToCameraDirection = normalize(viewPosition - fragPosition);
	vec3 reflectDirection = reflect(-fragToLightDirection, normalDirection);
	float specularFactor = pow(max(dot(fragToCameraDirection, reflectDirection), 0.0f), shineExponent);
	vec3 specular = specularIntensity * specularFactor * lightColor;

	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}