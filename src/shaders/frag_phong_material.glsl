#version 330 core

smooth in vec3 normal;
in vec3 fragPosition;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	int shininess;
};

uniform Material material;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 fragmentColor;

void main()
{
	// Ambient light
	vec3 ambient = lightColor * material.ambient;

	// Diffuse light
	vec3 normalDirection = normalize(normal);
	vec3 fragToLightDirection = normalize(lightPosition - fragPosition);
	float diffuseIntensity = max(dot(normalDirection, fragToLightDirection), 0.0f);
	vec3 diffuse = lightColor * (diffuseIntensity * material.diffuse);
	
	// Specular
	vec3 fragToCameraDirection = normalize(viewPosition - fragPosition);
	vec3 reflectDirection = reflect(-fragToLightDirection, normalDirection);
	float specularFactor = pow(max(dot(fragToCameraDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specular = lightColor * (specularFactor * material.specular);
	
	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}