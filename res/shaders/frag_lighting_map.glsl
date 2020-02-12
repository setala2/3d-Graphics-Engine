#version 330 core

smooth in vec3 normal;
in vec3 fragPosition;
in vec2 uv;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	int shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPosition;

out vec4 fragmentColor;

void main()
{
	// Ambient light
	vec3 ambient = light.ambient * texture(material.diffuse, uv).rgb;

	// Diffuse light
	vec3 normalDirection = normalize(normal);
	vec3 fragToLightDirection = normalize(light.position - fragPosition);
	float diffuseIntensity = max(dot(normalDirection, fragToLightDirection), 0.0f);
	vec3 diffuse = light.diffuse * diffuseIntensity * texture(material.diffuse, uv).rgb;
	
	// Specular
	vec3 fragToCameraDirection = normalize(viewPosition - fragPosition);
	vec3 reflectDirection = reflect(-fragToLightDirection, normalDirection);
	float specularFactor = pow(max(dot(fragToCameraDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specular = light.specular * specularFactor * texture(material.specular, uv).rgb;
	
	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}